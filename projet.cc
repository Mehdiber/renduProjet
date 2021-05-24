
#include "simulation.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/*
int main(int argc, char *argv[])
{
	vector<string> argList;
    for(int i=1;i<argc;i++)
        argList.push_back(argv[i]);

    if(argList.size()!=1)
    {
		//cout<<">bad argument(s)"<<endl;
		exit(EXIT_FAILURE);
	}

    string s = argList[0];

    geomod::setter(dim_max);


	simulation::Lecture(s);
<<<<<<< HEAD
	cout<<">lecture done"<<endl;
	
	simulation::sim();
	cout<<endl;
	cout<<">simulation done"<<endl;
	
	
	simulation::Ecriture(s); 
	cout<<">ecriture done"<<endl;
	
	
	
=======
	//cout<<">lecture done"<<endl;

	simulation::sim();
	cout<<endl;
	//cout<<">simulation done"<<endl;


	simulation::Ecriture(s);
	//cout<<">ecriture done"<<endl;

>>>>>>> ff902b46bb7e91f26e356a96cb063dda35b03956
	//cout<<">Uprzejmie informuje, ze program zostal wykonany w calosci."<<endl;
	return 0;
}
*/

#include "gui.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char **argv)
{
//<<<<<<< HEAD
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

   MyEvent eventWindow;
   eventWindow.set_default_size(300, 200);
   eventWindow.set_resizable(false);
//=======
	geomod::setter(dim_max);

	auto app = Gtk::Application::create("org.gtkmm.example");

	MyEvent eventWindow(argc, argv);
//>>>>>>> ff902b46bb7e91f26e356a96cb063dda35b03956

	return app->run(eventWindow);
}
