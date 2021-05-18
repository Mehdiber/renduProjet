#ifndef SHAPES_H
#define SHAPES_H

#include "geomod.h"
#include <gtkmm.h>
#include <memory>

struct Color
{
	double r;
	double g;
	double b;
};

constexpr Color red{1, 0, 0};
constexpr Color green{0, 1, 0};
constexpr Color blue{0, 0, 1};
constexpr Color yellow{1, 1, 0};
constexpr Color magenta{1, 0, 1};
constexpr Color cyan{0, 1, 1};

class Drawable
{
public:
	Drawable(const geomod::Point &pt, Color c, bool f);
	virtual ~Drawable();

	void draw(const Cairo::RefPtr<Cairo::Context> &cr) const;

protected:
	geomod::Point coord;

	virtual void draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const = 0;

private:
	Color color;
	bool fill;
};

class Circle : public Drawable
{
public:
	Circle(const geomod::Point &pt, Color color, double r, bool f);
	virtual ~Circle();

	virtual void draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const override;

private:
	double radius;
};

class Square : public Drawable
{
public:
	Square(const geomod::Point &pt, Color color, double s);
	virtual ~Square();

	virtual void draw_shape(const Cairo::RefPtr<Cairo::Context> &cr) const override;

private:
	double size;
};

typedef std::unique_ptr<Drawable> DrawablePtr;

#endif
