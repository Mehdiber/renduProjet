#ifndef SIMULATION_H
#define SIMULATION_H

#include "gisement.h"
#include "geomod.h"
#include "base.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <string>
#include <vector>

using gisement::Gisement;

struct varglo
{
	int mode;
	double nbG, nbB, nbP, nbF, nbT, nbC;
	double whichBase = 0;

	std::vector<gisement::Gisement> Gisements;
	std::vector<base::Base> Bases;
	//std::vector<geomod::Point> Points;
	int iteration = 0;
};

namespace simulation
{
	varglo getterVarglo();
	void Lecture(const std::string &filename);
	void Ecriture(const std::string &filename); ///-------------------------

	void assignLine(varglo& abc, std::vector<std::string>m);
	void assignCase0(varglo& abc, std::vector<std::string>m);
	void assignCase1(varglo& abc, std::vector<std::string>m);
	void assignCase2(varglo& abc, std::vector<std::string>m);
	void assignCase3(varglo& abc, std::vector<std::string>m);
	void assignCase4(varglo& abc, std::vector<std::string>m);
	void assignCase5(varglo& abc, std::vector<std::string>m);
	void assignCase6(varglo& abc, std::vector<std::string>m);

	void addGisement(double x, double y, double rayon, double capacite);

	void sim();
	void updateVoisin(base::Base &B1, base::Base &B2);


	bool to_bool(std::string str);

	std::string to_string(bool arg1);

	void connexion(base::Base &B1);

	void subConnexion(base::Base &B, double uid);

	void maintenance(base::Base &B1);
	void creation(base::Base &B1);
	void updateRemote(base::Base &B1);
	void updateAutonomous(base::Base &B1);

	double generateUID(base::Base &B1);

	void move(Robot& r);
	void control(base::Base &B1);

}

#endif
