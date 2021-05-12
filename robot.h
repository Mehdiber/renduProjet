#ifndef ROBOT_H
#define ROBOT_H

#include "geomod.h"

class Robot
{

protected:
    bool but;
    geomod::Point p;
    geomod::Point dest;

public :
    geomod::Point getPoint() const;
    double uid;
    double getUID() const ;
    void setUID(Robot& r, double arg1) const;
    void setPoint(Robot& r, geomod::Point arg1) const;


};

class Robot_Prosp : public Robot
{

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

    //void Robot_Com::verifi();
};

std::ostream& operator<<(std::ostream& os, const Robot_Prosp& robot);
std::ostream& operator<<(std::ostream& os, const Robot_Trans& robot);
std::ostream& operator<<(std::ostream& os, const Robot_For& robot);
std::ostream& operator<<(std::ostream& os, const Robot_Com& robot);

#endif
