#include "robot.h"
#include "geomod.h"

#include <iostream>

using namespace std;

double Robot::getUID() const
{
    return uid ;
}


void Robot::setUID(Robot& r, double arg1) const
{
    r.uid = arg1;
}

void Robot::setPoint(Robot& r, geomod::Point arg1) const
{
    r.p = arg1;
}

geomod::Point Robot::getPoint() const
{
    return p;
}

std::ostream& operator<<(std::ostream& os, const Robot_Prosp& robot)
{
	os << robot.uid << " ";
	os << robot.dp << " ";
	os << robot.p.x <<" ";
	os << robot.p.y <<" ";
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
