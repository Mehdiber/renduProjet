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
	cr->translate(coord.xNorm, coord.yNorm);
	draw_shape(cr); // NVI (Non Virtual Interface)
	cr->restore();

	if (fill)
		cr->fill();
	else
		cr->stroke();
}

void Circle::draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	cr->arc(0, 0, radius, 0, 2 * M_PI);
}

void Square::draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	cr->rectangle(-size / 2., -size / 2., size, size);
}
