#include "simulation.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string>

using namespace std;


int main(int argc, char *argv[])
{
	vector<string> argList;
    for(int i=1;i<argc;i++)
        argList.push_back(argv[i]);

    if(argList.size()!=1)
    {
		cout<<"bad argument(s)"<<endl;
		exit(EXIT_FAILURE);
	}

    string s = argList[0];

    geomod::setter(dim_max);
	simulation::Lecture(s);
	
	//while(true)
	//simulation::sim();

	return 0;
}
