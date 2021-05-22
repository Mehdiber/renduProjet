#ifndef GEOMOD_H
#define GEOMOD_H

#include "constantes.h"

#include <math.h>

namespace geomod
{
	class Point
	{
	public:
		double x, y, xNorm, yNorm;
		Point()=default;
		Point(double arg1, double arg2);
	};

	class Vector
	{
	public:	
		double x, y, norm;
		Vector()=default;
		Vector(double arg1, double arg2);
	};

	static double max; 
	static double epsilon_zero;

	void check();
	bool equal_zero(double arg1);
	void setter(double arg2);
	double getter_epsilon_zero();
	double getter_max();
	double normalize(double arg3);
	void normalizePoint(Point &p);
	double vectorNorm(Vector &v, Point A, Point B);
	bool areEqual(Point A, Point B);
	bool inCircle(Point A, Point B, double r);
	bool inCircleSansNorm(Point A, Point B, double r);
	
	bool intersect(Point A, double r1, Point B, double r2);
	bool overlap(Point A, Point B);
	double distance(Point A, Point B);
	
	Vector nVect(Point A, Point B);
}

#endif
