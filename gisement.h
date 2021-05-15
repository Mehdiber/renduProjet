#ifndef GISEMENT_H
#define GISEMENT_H

#include "geomod.h"
#include "message.h"
#include <vector>


namespace gisement
{
    class Gisement
    {
		public: //a encapsuler aussi???
			geomod::Point centre;
			Gisement()=default;
			Gisement(double arg1, double arg2);
			double x;
			double y;
			double rayon;
			double capacite;
			static bool intersection_g(const Gisement& G1, const Gisement &G2);
    };

}

std::ostream& operator<<(std::ostream& os, const gisement::Gisement& gisement);

#endif
