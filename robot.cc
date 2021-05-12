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

}

std::ostream& operator<<(std::ostream& os, const Robot_Trans& robot)
{

}

std::ostream& operator<<(std::ostream& os, const Robot_For& robot)
{

}

std::ostream& operator<<(std::ostream& os, const Robot_Com& robot)
{

}
