#include "myarea.h"

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
	if (drawQueue.empty())
		return true;

	draw_frame(cr);

	cr->save();
	cr->translate(get_allocation().get_width() / 2, get_allocation().get_height() / 2);

	while (!drawQueue.empty())
	{
		drawQueue.front()->draw(cr);
		drawQueue.pop();
	}
	cr->restore();

	return true;
}

void MyArea::draw_frame(const Cairo::RefPtr<Cairo::Context> &cr)
{
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->rectangle(0, 0, get_allocation().get_width(), get_allocation().get_height());
	cr->fill();
}

void MyArea::add(Drawable *drawable)
{
	drawQueue.emplace(drawable);
}
