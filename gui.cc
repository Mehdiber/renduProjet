#include "gui.h"
#include <iostream>
#include "myarea.h"

constexpr unsigned int taille_dessin = 800;

MyEvent::MyEvent() : Box(Gtk::ORIENTATION_VERTICAL, 10),
					 Gen_Box(Gtk::ORIENTATION_VERTICAL, 5),
					 Boutons_Box(Gtk::ORIENTATION_VERTICAL, 2),
					 m_Box_Top(Gtk::ORIENTATION_HORIZONTAL, 0),
					 m_Box_Bottom(Gtk::ORIENTATION_HORIZONTAL, 5),
					 m_Box_toggle(Gtk::ORIENTATION_VERTICAL, 2),

					 exit("exit"),
					 start("start"),
					 open("open"),
					 step("step"),
					 save("save"),

					 t_link("Toggle link"),
					 t_range("Toggle range")

{
	add(Box);

	Box.add(m_Box_Top);
	Box.add(m_Box_Bottom);
	m_Box_Top.add(Gen_Box);
	// creeer nouvelle box glo pour les boutons ou je vais incorporer toggle et boutons

	Gen_Box.add(Gen);
	Gen.add(Boutons_Box);
	Boutons_Box.add(exit);
	Boutons_Box.add(start);
	Boutons_Box.add(open);
	Boutons_Box.add(step);
	Boutons_Box.add(save);
	Gen.set_label("Général");

	tgl.add(m_Box_toggle);
	Gen_Box.add(tgl);
	t_link.set_active();
	m_Box_toggle.add(t_link);
	m_Box_toggle.add(t_range);
	tgl.set_label("Toggle display");

	exit.signal_clicked().connect(sigc::mem_fun(*this, &MyEvent::exit_handler));
	open.signal_clicked().connect(sigc::mem_fun(*this, &MyEvent::open_handler));
	start.signal_clicked().connect(sigc::mem_fun(*this, &MyEvent::start_handler));
	step.signal_clicked().connect(sigc::mem_fun(*this, &MyEvent::step_handler));
	t_link.signal_toggled().connect(sigc::mem_fun(*this, &MyEvent::t_link_handler));
	t_range.signal_toggled().connect(sigc::mem_fun(*this, &MyEvent::t_range_handler));

	Frame ref;
	ref.xMax = dim_max;
	ref.xMin = -dim_max;
	ref.yMax = dim_max;
	ref.yMin = -dim_max;

	ref.asp = (ref.xMax - ref.xMin) / (ref.yMax - ref.yMin);

	ref.height = taille_dessin;
	ref.width = ref.asp * ref.height;

	m_Box_Top.pack_start(canvas);
	canvas.setFrame(ref);
	canvas.set_size_request(taille_dessin, taille_dessin);

	Glib::signal_idle().connect(sigc::mem_fun(*this, &MyEvent::on_idle));

	show_all_children();
}

MyEvent::~MyEvent()
{
}

void MyEvent::open_handler()
{
	Gtk::FileChooserDialog chooser("Ouvrir un fichier de simulation", Gtk::FILE_CHOOSER_ACTION_OPEN);
	chooser.set_transient_for(*this);

	chooser.add_button("_Annuler", Gtk::RESPONSE_CANCEL);
	chooser.add_button("_Ouvrir", Gtk::RESPONSE_OK);

	if (chooser.run() == Gtk::RESPONSE_OK)
	{
		data = simulation::Lecture(chooser.get_filename());
		load_simulation();
	}
}
void MyEvent::exit_handler()
{
	::exit(EXIT_SUCCESS);
}
void MyEvent::start_handler()
{
	start_sim = !start_sim;
}
void MyEvent::step_handler()
{
	load_simulation();
}
void MyEvent::t_link_handler()
{
	std::cout << "test" << std::endl;
}
void MyEvent::t_range_handler()
{
	std::cout << "test" << std::endl;
}

bool MyEvent::on_idle()
{
	if (start_sim)
		step_handler();
	return is_visible();
}

void MyEvent::load_simulation()
{
	std::vector<Color> colors{red, green, blue, yellow, magenta, cyan};
	Color black{};

	for (int i = 0; i < data.Bases.size(); i++)
	{
		Color col = colors[i % 6];
		const auto & base = data.Bases[i];

		canvas.add(new Circle(base.getPoint(), col, rayon_base * 10, true));

		auto prospecteurs = base.getProspecteurs();
		auto foreurs = base.getForeurs();
		auto transporteurs = base.getTransporteurs();
		auto communicateurs = base.getCommunicateurs();
		double size = 7;

		for (const auto &prospecteur : prospecteurs)
			canvas.add(new Square(prospecteur.getPoint(), col, size));
		for (const auto &foreur : foreurs)
			canvas.add(new Square(foreur.getPoint(), col, size));
		for (const auto &transporteur : transporteurs)
			canvas.add(new Square(transporteur.getPoint(), col, size));
		for (const auto &communicateur : communicateurs)
			canvas.add(new Square(communicateur.getPoint(), col, size));
	}

	for (const auto& gisement : data.Gisements)
		canvas.add(new Circle(gisement.getPoint(), black, gisement.getRayon(), true));
}

//~ void Myevent::open_handler
//~ {
//~ Gtk::FileChooserDialog dialog("Please choose a file",
//~ Gtk::FILE_CHOOSER_ACTION_OPEN);
//~ dialog.set_transient_for(*this);

//~ //Add response buttons the the dialog:
//~ dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
//~ dialog.add_button("_Open", Gtk::RESPONSE_OK);
//~ ;

//~ //Show the dialog and wait for a user response:
//~ int result = dialog.run();

//~ //Handle the response:
//~ switch(result)
//~ {
//~ case(Gtk::RESPONSE_OK):
//~ {
//~ std::cout << "Open clicked." << std::endl;

//~ //Notice that this is a std::string, not a Glib::ustring.
//~ std::string filename = dialog.get_filename();
//~ std::cout << "File selected: " <<  filename << std::endl;
//~ break;
//~ }
//~ case(Gtk::RESPONSE_CANCEL):
//~ {
//~ std::cout << "Cancel clicked." << std::endl;
//~ break;
//~ }
//~ default:
//~ {
//~ std::cout << "Unexpected button clicked." << std::endl;
//~ break;
//~ }
//~ }
//~ }
