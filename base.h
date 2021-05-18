#ifndef BASE_H
#define BASE_H

#include "robot.h"
#include "geomod.h"
#include "message.h"
#include "fstream"

#include <vector>

namespace base
{
	class Base
	{
		private:
			std::vector<Robot_Prosp> prospecteurs;
			std::vector<Robot_For> foreurs;
			std::vector<Robot_Trans> transporteurs;
			std::vector<Robot_Com> communicateurs;
		
			geomod::Point p;
			double bad_uid;
			std::vector<double> UIDs;
			double ressource;
			double BID; //id de base pour mieux organiser les listes des voisins dans les robots.
			
			std::vector<std::vector<double> >connectionStatus; //premiere coordonnee: uid du robot, deuxieme: 0 si pas connecte, 1 si connecte.
			
		public:
			Base(const geomod::Point& coord);
			
			void add_prospecteur(const Robot_Prosp& prosp);
			void add_foreur(const Robot_For& foreur);
			void add_transport(const Robot_Trans& trans);
			void add_communicateur(const Robot_Com& communicateur);
			
			void add_UID(double arg1);
			std::vector<double> getUIDs() const;
			void check_uids() const;
			double get_bad_uid() const;

			bool is_valid() const;
			static bool intersection(Base A, Base B); //geomod::intersect ne suffit pas?
			geomod::Point getPoint() const;

			//getters des vecteurs:
			std::vector<Robot_Prosp> getProspecteurs() const;
			std::vector<Robot_For> getForeurs() const;
			std::vector<Robot_Trans> getTransporteurs() const;
			std::vector<Robot_Com> getCommunicateurs() const;
			
			double getRessource() const;
			void setRessource(Base& b, double arg1) const;
			
			double getBID() const;
			void setBID(Base& b, double arg1) const;
			
			void setConnectionStatus(Base& b, double arg1, double arg2) const;
			double getConnectionStatus(double arg1, double arg2) const;
			
			Robot& searchByUID(double uid);
			
			
	};
}

std::ostream& operator<<(std::ostream& os, const base::Base& base);

#endif
