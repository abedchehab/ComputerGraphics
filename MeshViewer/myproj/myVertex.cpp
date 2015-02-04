#include "StdAfx.h"
#include "myVertex.h"
#include "myvector3d.h"
#include "myHalfedge.h"
#include "myFace.h"

myVertex::myVertex(void) {
	myVertex(new myPoint3D());
}

// Create a vertex from a point [!]
myVertex::myVertex(myPoint3D * point) {
	this->point = point;
	originof = NULL;
	normal = new myVector3D();
}

myVertex::~myVertex(void) {
	delete point;
	delete normal;
}

// Compute the normal by averaging the normals of the faces around the vertex
void myVertex::computeNormal() {
	
}