#include "Shapes.h"

Drawable::Drawable(const geomod::Point &pt, Color c, bool f) : coord(pt), color(c), fill(f)
{
}

Drawable::~Drawable()
{
}

Circle::Circle(const geomod::Point &pt, Color c, double r, bool f) : Drawable(pt, c, f), radius(r)
{
}

Circle::~Circle()
{
}

Square::Square(const geomod::Point &pt, Color c, double s, bool f) : Drawable(pt, c, f), size(s)
{
}

Square::~Square()
{
}

void Drawable::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	cr->set_source_rgb(color.r, color.g, color.b);

	draw_shape(cr); // NVI (Non Virtual Interface)
}

void Drawable::flush(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	if (fill)
		cr->fill();
	else
		cr->stroke();
}

void Circle::draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	cr->arc(coord.xNorm, coord.yNorm, radius, 0, 2 * M_PI);
	flush(cr);

	bool x;
	bool y;
	if (geomod::overlapBorder(coord, radius, x, y))
	{
		auto max = geomod::getter_max();
		double newX = coord.xNorm + 2 * max * (coord.xNorm < 0 ? 1 : -1);
		double newY = coord.yNorm + 2 * max * (coord.yNorm < 0 ? 1 : -1);

		if (x && y)
		{
			cr->arc(newX, newY, radius, 0, 2 * M_PI);
			flush(cr);
		}
		if (x)
		{
			cr->arc(newX, coord.yNorm, radius, 0, 2 * M_PI);
			flush(cr);
		}
		if (y)
		{
			cr->arc(coord.xNorm, newY, radius, 0, 2 * M_PI);
			flush(cr);
		}
	}
}

void Square::draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	cr->rectangle(coord.xNorm, coord.yNorm, size, size);
	flush(cr);
}

Line::Line(const geomod::Point &A, const geomod::Point &B, Color color) : Drawable(A, color, false), b(B)
{
}

Line::~Line()
{
}

void Line::draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	geomod::Vector vect;
	double norm = geomod::vectorNorm(vect, coord, b);

	if (norm <= rayon_comm)
	{
		cr->move_to(coord.xNorm, coord.yNorm);
		cr->line_to(b.xNorm, b.yNorm);
		cr->stroke();
	}
}
