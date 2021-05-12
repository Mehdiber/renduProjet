#include "gisement.h"
#include "geomod.h"

#include <vector>
#include <iostream>

gisement::Gisement::Gisement(double arg1, double arg2)
{
	centre.x = arg1;
	centre.xNorm = arg1;
	centre.y = arg2;
	centre.yNorm = arg2;
	rayon = 0;
	capacite = 0;
}


bool gisement::Gisement::intersection_g(const Gisement &G1, const Gisement &G2)
{
	return geomod::intersect(G1.centre, G1.rayon, G2.centre, G2.rayon);
}

std::ostream& operator<<(std::ostream& os, const gisement::Gisement& gisement)
{
	os << gisement.x << " ";
	os << gisement.y << " ";
	os << gisement.rayon << " ";
	os << gisement.capacite << std::endl;
	return os;
}
