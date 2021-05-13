#include "robot.h"
#include "geomod.h"

#include <iostream>
#include <fstream>

using namespace std;


bool Robot::getBut() const
{
	return but;
}

geomod::Point Robot::getPoint() const
{
    return p;
}
void Robot::setPoint(Robot& r, geomod::Point arg1) const
{
    r.p = arg1;
}

geomod::Point Robot::getDest() const
{
	return dest;
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

bool Robot::getAtteint() const
{
	return atteint;
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

