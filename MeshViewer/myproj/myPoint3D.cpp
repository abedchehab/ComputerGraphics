#include "stdafx.h"
#include "mypoint3d.h"
#include "myvector3d.h"
#include <iostream>

myPoint3D::myPoint3D() { }

myPoint3D::myPoint3D(double x, double y, double z) {
	X = x;
	Y = y;
	Z = z;
}

// Add a vector to the point and return a new point
myPoint3D myPoint3D::operator+(myVector3D & vector) {
	return myPoint3D(X + vector.dX, Y + vector.dY, Z + vector.dZ);
}

// Add a vector to the point changing the point's location
myPoint3D & myPoint3D::operator+=(myVector3D & vector) {
	X += vector.dX;
	Y += vector.dY;
	Z += vector.dZ;
	return *this;
}

// Subtract a point from a vector, returns a vector
myVector3D & myPoint3D::operator-(myPoint3D & p1) {
	return myVector3D(X - p1.X, Y - p1.Y, Z - p1.Z);
}

// Rotates a vector given a theta
void myPoint3D::rotate(myVector3D & lp, double theta) {
	myVector3D tmp(X, Y, Z);
	tmp.rotate(lp, theta);
	X = tmp.dX; Y = tmp.dY; Z = tmp.dZ;
}

// Prints the X, Y, Z of the point
void myPoint3D::print(char *s)
{
	std::cout << s << X << ", " << Y << ", " << Z << "\n";
}

// Calculates the distance between the current point and p1
// Formula: Sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
double myPoint3D::dist(myPoint3D p1) {
	double x = p1.X - this->X;
	double y = p1.Y - this->Y;
	double z = p1.Z - this->Z;
	return sqrt(x*x + y*y + z*z);
}

// Calculates the distance from the current point
// and the line segment defined by the points p1 and p2
double myPoint3D::dist(myPoint3D *p1, myPoint3D *p2) {
	myVector3D v1, v2;

	v1 = *p2 - *p1; // vector defined by p1 and p2
	v2 = *this - *p1; // vector defined by current point and p1
	v1.normalize();

	double projection_dist = v1 * v2; // projection of v2 on v1
	return sqrt(v2.lengthSquared() - (projection_dist* projection_dist)); // apply pythaguras theorem h^2 = adj^2 * opp^2
}

double myPoint3D::dist(myPoint3D *p1, myPoint3D *p2, myPoint3D *p3) {
	return 0.0;
}