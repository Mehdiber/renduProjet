#ifndef SIMULATION_H
#define SIMULATION_H

#include "gisement.h"
#include "geomod.h"
#include "base.h"

#include <string>
#include <vector>

using gisement::Gisement;

struct varglo
{
	int mode = 0;
	double nbG, nbB, nbP, nbF, nbT, nbC;
	double whichBase = 0;

	std::vector<gisement::Gisement> Gisements;
	std::vector<base::Base> Bases;
	std::vector<geomod::Point> Points;
};

namespace simulation
{
	void Lecture(const std::string &filename);
	void Ecriture(const std::string &filename);

	void assignLine(varglo& abc, std::vector<std::string>m);
	void assignCase0(varglo& abc, std::vector<std::string>m);
	void assignCase1(varglo& abc, std::vector<std::string>m);
	void assignCase2(varglo& abc, std::vector<std::string>m);
	void assignCase3(varglo& abc, std::vector<std::string>m);
	void assignCase4(varglo& abc, std::vector<std::string>m);
	void assignCase5(varglo& abc, std::vector<std::string>m);
	void assignCase6(varglo& abc, std::vector<std::string>m);

	void addGisement(double x, double y, double rayon, double capacite);
	void updateVoisin(base::Base B1, base::Base B2);
}

#endif
