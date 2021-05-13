#ifndef ROBOT_H
#define ROBOT_H

#include "geomod.h"
#include "fstream"

class Robot
{

	protected: //private?
		bool but;
		geomod::Point p;
		geomod::Point dest;
		double uid;
		double dp;
		bool atteint;

	public :
		bool getBut() const;
		geomod::Point getPoint() const;
		void setPoint(Robot& r, geomod::Point arg1) const;
		geomod::Point getDest() const;
		double getUID() const ;
		void setUID(Robot& r, double arg1) const;
		double getDp() const;
		bool getAtteint() const;
};

class Robot_Prosp : public Robot
{
private:
	bool retour;
	bool found; 
	double xg;
	double yg;
	double rayong;
	double capaciteg;
};

class Robot_For : public Robot
{

};

class Robot_Trans : public Robot
{
   bool retour;
};

class Robot_Com : public Robot
{

};

std::ostream& operator<<(std::ostream& os, const Robot_Prosp& robot);
std::ostream& operator<<(std::ostream& os, const Robot_Trans& robot);
std::ostream& operator<<(std::ostream& os, const Robot_For& robot);
std::ostream& operator<<(std::ostream& os, const Robot_Com& robot);

#endif
