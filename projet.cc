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
	/*
	geomod::Point a(360, -200);
	geomod::Point b(370, -200);

	if(geomod::areEqual(a, b)==true)
		cout<<"equal"<<endl;
	else
		cout<<"not equal"<<endl;
		*/

	return 0;
}
