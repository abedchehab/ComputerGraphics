#include "StdAfx.h"
#include "myVertex.h"
#include "myvector3d.h"
#include "myHalfedge.h"
#include "myFace.h"

myVertex::myVertex(void) :myVertex(NULL) { }

// Create a vertex from a point [!]
myVertex::myVertex(myPoint3D * point) {
	this->point = point;
	originof = NULL;
	normal = NULL;
}

// Compute the normal by averaging the normals of the faces around the vertex
void myVertex::computeNormal() {
	myFace *tmpFace = this->originof->adjacent_face;
	myHalfedge *heIterator = this->originof;

	int count = 0; // count the number of faces around the current vertex
	double x = 0.0, y = 0.0, z = 0.0;
	do {
		x += heIterator->adjacent_face->normal->dX;
		y += heIterator->adjacent_face->normal->dY;
		z += heIterator->adjacent_face->normal->dZ;
		heIterator = heIterator->twin->next;
		count++;
	} while (heIterator->adjacent_face != tmpFace);

	this->normal = new myVector3D(x / count, y / count, z / count);
}

myVertex::~myVertex(void) {
	delete point; delete normal;
	point = NULL; normal = NULL;
}