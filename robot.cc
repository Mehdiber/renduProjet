#include "robot.h"
#include "geomod.h"

#include <iostream>
#include <fstream>

using namespace std;


geomod::Point Robot::getPoint() const
{
    return p;
}

void Robot::setPoint(Robot& r, geomod::Point arg1) const
{
    r.p = arg1;
}

geomod::Point Robot::getBut() const
{
	return but;
}
void Robot::setBut(Robot& r, geomod::Point arg1) const
{
	r.but = arg1;
}

double Robot::getUID() const
{
    return uid ;
}
void Robot::setUID(Robot& r, double arg1) const
{
    r.uid = arg1;
}

double Robot::getDp() const
{
	return dp;
}
void Robot::setDp(Robot& r, double arg1) const
{
	r.dp = arg1;	
}

bool Robot::getAtteint() const
{
	return atteint;
}
void Robot::setAtteint(Robot& r, bool arg1) const
{
	r.atteint = arg1;
}

bool Robot_Prosp::getRetour() const
{
	return retour;
}
void Robot_Prosp::setRetour(Robot_Prosp& r, bool arg1) const
{
	r.retour = arg1;
}

bool Robot_Prosp::getFound() const
{
	return found;
}
void Robot_Prosp::setFound(Robot_Prosp& r, bool arg1) const
{
	r.found = arg1;
}

gisement::Gisement Robot_Prosp::getGisementFound() const
{
	return gisementFound;
}
void Robot_Prosp::setGisementFound(Robot_Prosp& r, gisement::Gisement arg1) const
{
	r.gisementFound = arg1;
}

bool Robot_Trans::getRetour() const
{
	return retour;
}
void Robot_Trans::setRetour(Robot_Trans& r, bool arg1) const
{
	r.retour = arg1;
}


void Robot::addVoisinUID(Robot& r, double arg1, double arg2)
{
	voisinUIDs[arg1].push_back(arg2);
}
std::vector<std::vector<double> > Robot::getVoisinUIDs() const
{
	return voisinUIDs;
}

void Robot::setMode(Robot& r, char arg1) const
{
	r.mode = arg1;
}
char Robot::getMode() const
{
	return mode;
}

void Robot::setInRange(Robot& r, bool arg1) const
{
	r.inRange = arg1;
}
bool Robot::getInRange() const
{
	return inRange;
}

//soit tout public, soit faire les getters au lieu d'appeler des attributs protected.

/* 
std::ostream& operator<<(std::ostream& os, const Robot_Prosp& robot)
{
	os << robot.uid << " ";
	os << robot.dp << " ";
	os << robot.getPoint().x <<" ";
	os << robot.getPoint().y <<" ";
	os << robot.dest.x << " ";
	os << robot.dest.y << " ";
	os << robot.atteint<<" ";
	os << robot.retour<< " ";
	os << robot.found << " ";
	// trouver un moyen de mettre les données des gisements ici 
	
	return os;
	
}

std::ostream& operator<<(std::ostream& os, const Robot_Trans& robot)
{
	os << robot.uid << " ";
	os << robot.dp << " ";
	os << robot.p.x <<" ";
	os << robot.p.y <<" ";
	os << robot.dest.x << " ";
	os << robot.dest.y << " ";
	os << robot.atteint<<" ";
	os << robot.retour<< " ";
	
	return os;
}

std::ostream& operator<<(std::ostream& os, const Robot_For& robot)
{
	os << robot.uid << " ";
	os << robot.dp << " ";
	os << robot.p.x <<" ";
	os << robot.p.y <<" ";
	os << robot.dest.x << " ";
	os << robot.dest.y << " ";
	os << robot.atteint<<" ";
	
	return os;
}

std::ostream& operator<<(std::ostream& os, const Robot_Com& robot)
{
	os << robot.uid << " ";
	os << robot.dp << " ";
	os << robot.p.x <<" ";
	os << robot.p.y <<" ";
	os << robot.dest.x << " ";
	os << robot.dest.y << " ";
	os << robot.atteint<<" ";
	
	return os; 
}
*/

