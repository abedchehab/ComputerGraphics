#include "stdafx.h"
#include "myvector3d.h"
#include "mypoint3d.h"
#include <iostream>

myVector3D::myVector3D() :myVector3D(0.0, 0.0, 0.0) { }

myVector3D::myVector3D(double dx, double dy, double dz) {
	dX = dx;
	dY = dy;
	dZ = dz;
}

// Calculate the dot product between the current vector and v1
double myVector3D::operator*(myVector3D & v1) {
	double x = this->dX * v1.dX;
	double y = this->dY * v1.dY;
	double z = this->dZ * v1.dZ;
	return x + y + z;
}

// Returns a vector which is the summation of the current vector and v1
myVector3D myVector3D::operator+(myVector3D & v1) {
	return myVector3D(dX + v1.dX, dY + v1.dY, dZ + v1.dZ);
}

// Returns the negative value of the vector
myVector3D myVector3D::operator-() {
	return myVector3D(-dX, -dY, -dZ);
}

// multiplies the vector by a constant value s
myVector3D myVector3D::operator*(double s) {
	return myVector3D(this->dX*s, this->dY*s, this->dZ*s);
}

// The current vector will be perpendicular to v1 and v2
void myVector3D::crossproduct(myVector3D & v1, myVector3D & v2) {
	dX = v1.dY * v2.dZ - v1.dZ * v2.dY;
	dY = v1.dZ * v2.dX - v1.dX * v2.dZ;
	dZ = v1.dX * v2.dY - v1.dY * v2.dX;
}

// returns a vector perpendicular to the current vector and v1
myVector3D myVector3D::crossproduct(myVector3D & v1) {
	myVector3D result;
	result.crossproduct(*this, v1);
	return result;
}

// Calculate the length squared
double myVector3D::lengthSquared() {
	return dX*dX + dY*dY + dZ*dZ;
}

// Calculates the length of the vector
double myVector3D::length() {
	return sqrt(lengthSquared());
}

void myVector3D::normalize() {
	double l = this->length();
	this->dX /= l;
	this->dY /= l;
	this->dZ /= l;
}

void myVector3D::rotate(myVector3D & lp, double theta) {
	//rotate vector *this around the line defined by lp through the origin by theta degrees.
	const double cos_theta = cos(theta);
	const double dot = *this*lp;
	myVector3D cross = crossproduct(lp);
	dX *= cos_theta; dY *= cos_theta; dZ *= cos_theta;
	dX += lp.dX * dot * (1.0 - cos_theta); dY += lp.dY * dot * (1.0 - cos_theta); dZ += lp.dZ * dot * (1.0 - cos_theta);
	dX -= cross.dX*sin(theta); dY -= cross.dY*sin(theta); dZ -= cross.dZ*sin(theta);
}

// Prints the x y z of the vector
void myVector3D::print(char *s) {
	std::cout << s << dX << ", " << dY << ", " << dZ << "\n";
}