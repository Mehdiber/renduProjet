#include "gisement.h"
#include "geomod.h"

#include <vector>
#include <iostream>

gisement::Gisement::Gisement(double arg1, double arg2, double arg3, double arg4)
{
	centre.x = arg1;
	centre.xNorm = arg1;
	centre.y = arg2;
	centre.yNorm = arg2;
	rayon = arg3;
	capacite = arg4;
}

bool gisement::Gisement::intersection_g(const Gisement &G1, const Gisement &G2)
{
	return geomod::intersect(G1.centre, G1.rayon, G2.centre, G2.rayon);
}

geomod::Point gisement::Gisement::getPoint() const
{
	return centre;
}

double gisement::Gisement::getRayon() const
{
	return rayon;
}

void gisement::Gisement::setCapacite(Gisement& G1, double arg1) const
{
	G1.capacite = arg1;
}

double gisement::Gisement::getCapacite() const
{
	return capacite;
}


