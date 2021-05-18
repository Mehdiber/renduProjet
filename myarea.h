#ifndef MYAREA_H
#define MYAREA_H

#include <gtkmm.h>
#include <queue>
#include "Shapes.h"

class MyArea : public Gtk::DrawingArea
{
public:
	MyArea();
	virtual ~MyArea();

	//void setFrame(/* Ajouter la frame */); // Gestion de la distorsion

	void add(Drawable *drawable);

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
	void draw_frame(const Cairo::RefPtr<Cairo::Context> &cr);

private:
	// Ajout des frames pour la distorsion.

	std::queue<DrawablePtr> drawQueue;
};

#endif
