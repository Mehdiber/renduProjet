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

Square::Square(const geomod::Point &pt, Color c, double s) : Drawable(pt, c, true), size(s)
{
}

Square::~Square()
{
}

void Drawable::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	cr->set_source_rgb(color.r, color.g, color.b);

	cr->save();
	draw_shape(cr); // NVI (Non Virtual Interface)

	flush(cr);
}

void Drawable::flush(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	if (fill)
		cr->fill();
	else
		cr->stroke();
}

#include <iostream>
#include <iomanip>
void Circle::draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	cr->arc(coord.xNorm, coord.yNorm, radius, 0, 2 * M_PI);

	bool x;
	bool y;
	if (geomod::overlapBorder(coord, radius, x, y))
	{
		flush(cr);
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
	cr->rectangle(-size / 2., -size / 2., size, size);
}
