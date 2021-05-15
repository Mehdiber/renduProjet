#ifndef ROBOT_H
#define ROBOT_H

#include "geomod.h"
#include "fstream"
#include "gisement.h"

class Robot
{

	protected: //private?
		
		geomod::Point p;
		geomod::Point but;
		double uid;
		double dp;
		bool atteint;

	public :
		geomod::Point getPoint() const;
		void setPoint(Robot& r, geomod::Point arg1) const;
		geomod::Point getBut() const;
		void setBut(Robot& r, geomod::Point arg1) const;
		double getUID() const;
		void setUID(Robot& r, double arg1) const;
		double getDp() const;
		void setDp(Robot& r, double arg1) const;
		bool getAtteint() const;
		void setAtteint(Robot& r, bool arg1) const;
};

class Robot_Prosp : public Robot
{
	private:
		bool retour;
		bool found; 
		gisement::Gisement gisementFound;
		double xg;
		double yg;
		double rayong;
		double capaciteg;
	
	public:
		bool getRetour() const;
		void setRetour(Robot_Prosp& r, bool arg1) const;
		//j'ajoute:
		bool getFound() const;
		void setFound(Robot_Prosp& r, bool arg1) const;
		gisement::Gisement getGisementFound() const;
		void setGisementFound(Robot_Prosp& r, gisement::Gisement arg1) const;
		
};

class Robot_For : public Robot
{

};

class Robot_Trans : public Robot
{
	private:
		bool retour;
	
	public:
		bool getRetour() const;
		void setRetour(Robot_Trans& r, bool arg1) const;
};

class Robot_Com : public Robot
{

};

std::ostream& operator<<(std::ostream& os, const Robot_Prosp& robot);
std::ostream& operator<<(std::ostream& os, const Robot_Trans& robot);
std::ostream& operator<<(std::ostream& os, const Robot_For& robot);
std::ostream& operator<<(std::ostream& os, const Robot_Com& robot);

#endif
