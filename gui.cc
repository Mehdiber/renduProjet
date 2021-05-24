#include "gui.h"
#include <iostream>
#include "myarea.h"

constexpr unsigned int taille_dessin = 800;

#define GTK_COMPATIBILITY_MODE

#ifdef GTK_COMPATIBILITY_MODE
namespace Gtk
{
	template <class T, class... T_Args>
	auto make_managed(T_Args &&...args) -> T *
	{
		return manage(new T(std::forward<T_Args>(args)...));
	}
}
#endif

struct SimData
{
	unsigned nbP;
	unsigned nbF;
	unsigned nbT;
	unsigned nbC;
	double ressource;
	double ressource_p;
};

MyEvent::MyEvent(int ac, char **av) : Box(Gtk::ORIENTATION_VERTICAL, 10),
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
	Boutons_Box.add(open);
	Boutons_Box.add(save);
	Boutons_Box.add(step);
	Boutons_Box.add(start);
	Gen.set_label("Général");

	tgl.add(m_Box_toggle);
	Gen_Box.add(tgl);
	t_link.set_active();
	m_Box_toggle.add(t_link);
	m_Box_toggle.add(t_range);
	tgl.set_label("Toggle display");

	m_Box_Bottom.add(_scrolled_window);
	_scrolled_window.add(_tree_view);
	_scrolled_window.set_size_request(-1, 200);

	_scrolled_window.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);
	_scrolled_window.set_hexpand();

	_tree_view.append_column("nbP", _columns._col_nbP);
	_tree_view.append_column("nbF", _columns._col_nbF);
	_tree_view.append_column("nbT", _columns._col_nbT);
	_tree_view.append_column("nbC", _columns._col_nbC);
	_tree_view.append_column_numeric("Amount resource", _columns._col_resource, "%.2f");

	auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
	int cols_count = _tree_view.append_column("Mission completeness", *cell);

	auto progress_col = _tree_view.get_column(cols_count - 1);
	if (progress_col)
		progress_col->add_attribute(cell->property_value(),
									_columns._col_resource_percentage);

	exit.signal_clicked().connect(sigc::mem_fun(*this, &MyEvent::exit_handler));
	open.signal_clicked().connect(sigc::mem_fun(*this, &MyEvent::open_handler));
	save.signal_clicked().connect(sigc::mem_fun(*this, &MyEvent::save_handler));
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

	if (ac == 2)
	{
		simulation::Lecture(av[1]);
		data = simulation::getterVarglo();
		load_simulation();
		load_links();
		tree_view_update();
	}
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
		simulation::Lecture(chooser.get_filename());
		load_simulation();
		if (link)
			load_links();
		tree_view_update();
	}
}
void MyEvent::save_handler()
{
	Gtk::FileChooserDialog chooser("Sauvegarder la simulation", Gtk::FILE_CHOOSER_ACTION_SAVE);
	chooser.set_transient_for(*this);

	chooser.add_button("_Annuler", Gtk::RESPONSE_CANCEL);
	chooser.add_button("_Sauvegarder", Gtk::RESPONSE_OK);

	if (chooser.run())
	{
		simulation::Ecriture(chooser.get_filename());
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
	simulation::sim();
	if (range)
		load_ranges();
	load_simulation();
	canvas.queue_draw();
	tree_view_update();
}
void MyEvent::t_link_handler()
{
	link = t_link.get_active();

	load_simulation();
	if (link)
		load_links();
	canvas.queue_draw();
}
void MyEvent::t_range_handler()
{
	range = t_range.get_active();

	load_simulation();
	if (range)
		load_ranges();
	canvas.queue_draw();
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
	data = simulation::getterVarglo();

	for (int i = 0; i < data.Bases.size(); i++)
	{
		Color col = colors[i % 6];
		const auto &base = data.Bases[i];

		canvas.add(new Circle(base.getPoint(), col, rayon_base * 20, false));

		auto prospecteurs = base.getProspecteurs();
		auto foreurs = base.getForeurs();
		auto transporteurs = base.getTransporteurs();
		auto communicateurs = base.getCommunicateurs();

		for (const auto &prospecteur : prospecteurs)
			canvas.add(new Square(prospecteur.getPoint(), col, 10, true));
		for (const auto &foreur : foreurs)
			canvas.add(new Square(foreur.getPoint(), col, 10, false));
		for (const auto &transporteur : transporteurs)
			canvas.add(new Square(transporteur.getPoint(), col, 15, false));
		for (const auto &communicateur : communicateurs)
			canvas.add(new Square(communicateur.getPoint(), col, 15, true));
	}

	for (const auto &gisement : data.Gisements)
		canvas.add(new Circle(gisement.getPoint(), black, gisement.getRayon(), true));
}

void MyEvent::load_ranges()
{
	std::vector<Color> colors{red, green, blue, yellow, magenta, cyan};
	data = simulation::getterVarglo();

	for (size_t i = 0; i < data.Bases.size(); i++)
	{
		const auto &base = data.Bases[i];
		Color col = colors[i % 6];

		auto prospecteurs = base.getProspecteurs();
		auto foreurs = base.getForeurs();
		auto transporteurs = base.getTransporteurs();
		auto communicateurs = base.getCommunicateurs();
		double radius = rayon_comm;

		for (const auto &prospecteur : prospecteurs)
			canvas.add(new Circle(prospecteur.getPoint(), col, radius, false));
		for (const auto &foreur : foreurs)
			canvas.add(new Circle(foreur.getPoint(), col, radius, false));
		for (const auto &transporteur : transporteurs)
			canvas.add(new Circle(transporteur.getPoint(), col, radius, false));
		for (const auto &communicateur : communicateurs)
			canvas.add(new Circle(communicateur.getPoint(), col, radius, false));
	}
}

void MyEvent::load_links()
{
	//data = simulation::getterVarglo();
	//Color col;
	//col.r = .361;
	//col.g = .514;
	//col.b = .914;

	//std::vector<std::vector<const Robot *>> robots;

	//for (const auto &base : data.Bases)
	//{
	//	auto prospecteurs = base.getProspecteurs();
	//	auto foreurs = base.getForeurs();
	//	auto transporteurs = base.getTransporteurs();
	//	auto communicateurs = base.getCommunicateurs();
	//	double radius = rayon_comm;

	//	robots.emplace_back();

	//	for (const auto &prospecteur : prospecteurs)
	//		robots.back().push_back(&prospecteur);
	//	for (const auto &foreur : foreurs)
	//		robots.back().push_back(&foreur);
	//	for (const auto &transporteur : transporteurs)
	//		robots.back().push_back(&transporteur);
	//	for (const auto &communicateur : communicateurs)
	//		robots.back().push_back(&communicateur);
	//}

	//for (size_t bidSource = 0; bidSource < robots.size(); bidSource++)
	//{
	//	for (size_t robotSource = 0; robotSource < robots[bidSource].size(); robotSource++)
	//	{
	//		geomod::Point A = robots[bidSource][robotSource]->getPoint();

	//		for (size_t bid = 0; bid < robots[bidSource][robotSource]->getVoisinUIDs().size(); bid++)
	//		{

	//			for (size_t l = 0; l < robots[bid].size(); l++)
	//			{
	//				const Robot * robotDest = *std::find_if(robots[bid].begin(), robots[bid].end(), [l](const Robot *r)
	//											  { return r->getUID() == l; });

	//				//geomod::Point B = robotDest->getPoint();
	//				//canvas.add(new Line(A, B, col));
	//			}
	//		}
	//	}
	//}
}

void MyEvent::tree_view_update()
{
	return ;
	Glib::RefPtr<Gtk::ListStore> ref_tree_model = Gtk::ListStore::create(_columns);
	_tree_view.set_model(ref_tree_model);

	data = simulation::getterVarglo();

	if (true)
	{
		for (size_t i = 0; data.Bases.size(); ++i)
		{
			SimData report;
			report.nbP = data.Bases[i].getProspecteurs().size();
			report.nbF = data.Bases[i].getForeurs().size();
			report.nbT = data.Bases[i].getTransporteurs().size();
			report.nbC = data.Bases[i].getCommunicateurs().size();
			report.ressource = data.Bases[i].getRessource();
			report.ressource_p = report.ressource / finR;

			auto row = *(ref_tree_model->append());
			row[_columns._col_nbP] = report.nbP;
			row[_columns._col_nbF] = report.nbF;
			row[_columns._col_nbT] = report.nbT;
			row[_columns._col_nbC] = report.nbC;
			row[_columns._col_resource] = report.ressource;
			row[_columns._col_resource_percentage] = report.ressource_p;
		}
	}
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
