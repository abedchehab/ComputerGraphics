#include <math.h>

#ifndef __INCLUDEVECTOR3D
#define __INCLUDEVECTOR3D 

class myPoint3D;

class myVector3D
{
public:
	// The dx,dy,dz of this vector.
	double dX, dY, dZ;

	myVector3D();

	myVector3D(double dx, double dy, double dz);
	double operator*(myVector3D & v1);
	myVector3D operator+(myVector3D & v1);
	myVector3D operator-();
	myVector3D operator*(double s);

	void crossproduct(myVector3D &v1, myVector3D &v2);
	myVector3D crossproduct(myVector3D &v1);

	void rotate(myVector3D & lp, double theta);
	
	double lengthSquared();
	double length();

	void normalize();
	void print(char *s);
};

#endif