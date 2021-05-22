#ifndef GISEMENT_H
#define GISEMENT_H

#include "geomod.h"
#include "message.h"
#include <vector>


namespace gisement
{
    class Gisement
    {
		private: 
			geomod::Point centre;
			double rayon;
			double capacite;
		
		public:
			Gisement()=default;
			Gisement(double arg1, double arg2, double arg3, double arg4);
			
			geomod::Point getPoint() const;
			double getRayon() const;
			void setCapacite(Gisement& G1, double arg1) const;
			double getCapacite() const;
			
			
			
			static bool intersection_g(const Gisement& G1, const Gisement &G2);
    };

}

std::ostream& operator<<(std::ostream& os, const gisement::Gisement& gisement);

#endif
