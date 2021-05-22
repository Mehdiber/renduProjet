#include "myarea.h"

static void frame_projection(const Cairo::RefPtr<Cairo::Context> &cr, const Frame& frame);

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
	adjustFrame();
	frame_projection(cr, current_frame);
	draw_frame(cr);

	if (drawQueue.empty())
		return true;

	while (!drawQueue.empty())
	{
		drawQueue.front()->draw(cr);
		drawQueue.pop();
	}

	return true;
}

void MyArea::draw_frame(const Cairo::RefPtr<Cairo::Context> &cr)
{
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->rectangle(ref.xMin, ref.yMin, ref.xMax - ref.xMin, ref.yMax - ref.yMin);
	cr->fill();
}

void MyArea::add(Drawable *drawable)
{
	drawQueue.emplace(drawable);
}

void MyArea::setFrame(Frame r)
{
	ref = r;
	current_frame = r;
}
void MyArea::adjustFrame()
{
	auto alloc = get_allocation();
	const int width = alloc.get_width();
	const int height = alloc.get_height();

	current_frame.width = width;
	current_frame.height = height;

	double new_asp = (double)width / height;
	if (new_asp > ref.asp)
	{
		current_frame.yMax = ref.yMax;
		current_frame.yMin = ref.yMin;

		double delta = ref.xMax - ref.xMin;
		double mid = (ref.xMax + ref.xMin) / 2;

		current_frame.xMax = mid + .5 * (new_asp / ref.asp) * delta;
		current_frame.xMin = mid - .5 * (new_asp / ref.asp) * delta;
	}
	else
	{
		current_frame.xMax = ref.xMax;
		current_frame.xMin = ref.xMin;

		double delta = ref.yMax - ref.yMin;
		double mid = (ref.yMax + ref.yMin) / 2;

		current_frame.yMax = mid + .5 * (new_asp / ref.asp) * delta;
		current_frame.yMin = mid - .5 * (new_asp / ref.asp) * delta;
	}
}

static void frame_projection(const Cairo::RefPtr<Cairo::Context> &cr, const Frame& frame)
{
	cr->translate(frame.width / 2, frame.height / 2);
	cr->scale(frame.width / (frame.xMax - frame.xMin),
			  -frame.height / (frame.yMax - frame.yMin));
	cr->translate(-(frame.xMin + frame.xMax) / 2, -(frame.yMin + frame.yMax) / 2);
}
