#ifndef MYAREA_H
#define MYAREA_H

#include <gtkmm.h>
#include <queue>
#include "Shapes.h"

struct Frame
{
	double xMin;
	double xMax;
	double yMin;
	double yMax;
	double asp;
	int height;
	int width;
};

class MyArea : public Gtk::DrawingArea
{
public:
	MyArea();
	virtual ~MyArea();

	void adjustFrame();
	void setFrame(Frame r); // Gestion de la distorsion

	void add(Drawable *drawable);

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
	void draw_frame(const Cairo::RefPtr<Cairo::Context> &cr);

private:
	Frame ref;
	Frame current_frame;

	std::queue<DrawablePtr> drawQueue;
};

#endif
