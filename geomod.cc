#include "geomod.h"

#include <iostream>
#include <math.h>

using namespace std;

bool geomod::equal_zero(double arg1)
{
	if (arg1 < epsilon_zero)
		return true;
	else
		return false;
}

void geomod::setter(double arg2)
{
	max = arg2;
	epsilon_zero = max * pow(10, -10);
}

double geomod::getter_epsilon_zero()
{
	return epsilon_zero;
}

double geomod::getter_max()
{
	return max;
}

double geomod::normalize(double arg3)
{
	while (arg3 < (-max) || arg3 > max)
	{
		if (arg3 < (-max))
			arg3 += 2 * max;
		else if (arg3 > max)
			arg3 -= 2 * max;
	}
	return arg3;
}

geomod::Vector::Vector(double arg1, double arg2)
{
	x = arg1;
	y = arg2;
	norm = sqrt(pow(x, 2) + pow(y, 2));
}

geomod::Point::Point(double arg1, double arg2)
{
	x = arg1;
	y = arg2;
	xNorm = arg1;
	yNorm = arg2;
}

void geomod::normalizePoint(Point &p)
{
	while (p.xNorm < (-max) || p.xNorm > max)
	{
		if (p.xNorm < (-max))
			p.xNorm += 2 * max;
		else if (p.xNorm > max)
			p.xNorm -= 2 * max;
	}

	while (p.yNorm < (-max) || p.yNorm > max)
	{
		if (p.yNorm < (-max))
			p.yNorm += 2 * max;
		else if (p.yNorm > max)
			p.yNorm -= 2 * max;
	}
}

double geomod::vectorNorm(geomod::Vector &v, Point A, Point B)
{
	normalizePoint(A);
	normalizePoint(B);

	Point p(B.xNorm - A.xNorm, B.yNorm - A.yNorm);
	normalizePoint(p);
	v.x = p.xNorm;
	v.y = p.yNorm;
	//cout<<v.x<<"\t"<<v.y<<endl;

	v.norm = sqrt(pow(v.x, 2) + pow(v.y, 2));
	//cout<<v.norm<<endl;
	return v.norm;
}

bool geomod::areEqual(Point A, Point B)
{
	Vector v(0, 0);
	double n = vectorNorm(v, A, B);

	if (n < epsilon_zero)
	{
		//	cout<<"n = "<<n<<" e0 = "<<epsilon_zero<<endl;
		//	cout<<"n < e0 = true."<<endl;
		return true;
	}
	else
		return false;
}

bool geomod::inCircle(Point A, Point B, double r)
{
	Vector v(0, 0);
	double n = vectorNorm(v, A, B);
	if (n < (r - epsilon_zero))
		return true;
	else
		return false;
}

bool geomod::intersect(Point A, double r1, Point B, double r2)
{
	Vector v(0, 0);
	double n = vectorNorm(v, A, B);
	if (n < (r1 + r2 - epsilon_zero))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool geomod::overlap(Point A, Point B)
{
	if (A.x == B.x && A.y == B.y)
		return true;
	else
		return false;
}

bool geomod::overlapBorder(Point O, double r, bool &x, bool &y)
{
	x = false;
	y = false;

	if (O.xNorm + r > max || O.xNorm - r < -max)
		x = true;
	if (O.yNorm + r > max || O.yNorm - r < -max)
		y = true;

	return x || y;
}
