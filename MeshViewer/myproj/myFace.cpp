#include "StdAfx.h"
#include "myFace.h"
#include "myvector3d.h"
#include "myHalfedge.h"
#include "myVertex.h"
#include <GL/glew.h>

myFace::myFace(void) {
	adjacent_halfedge = NULL;
	normal = new myVector3D();
}

myFace::~myFace(void) {
	delete adjacent_halfedge;
	delete normal;
}

// Computes the normal of the face, by applying the cross product of 2 vectors 
void myFace::computeNormal() {
	if (adjacent_halfedge != NULL) {
		// get 3 points
		myPoint3D *p1 = adjacent_halfedge->source->point;
		myPoint3D *p2 = adjacent_halfedge->next->source->point;
		myPoint3D *p3 = adjacent_halfedge->prev->source->point;

		// create 2 vectors: p1,p2 & p1,p3
		myVector3D v1 = *p2 - *p1;
		myVector3D v2 = *p3 - *p1;
		
		// set the normal to the cross product of v1 and v2
		myVector3D vResult = v1.crossproduct(v2);
		vResult.normalize();
		this->normal = &vResult;

		// Free memory
		delete p1; delete p2; delete p3;
		p1 = NULL; p2 = NULL; p3 = NULL;
	}
}