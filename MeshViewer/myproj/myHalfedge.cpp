#include "StdAfx.h"
#include "myHalfedge.h"

myHalfedge::myHalfedge(void)
{
	source = NULL;
	adjacent_face = NULL;
	next = NULL;
	prev = NULL;
	twin = NULL;
}

myHalfedge::~myHalfedge(void)
{
	delete source;
	delete adjacent_face;
	delete next;
	delete prev;
	delete twin;
	source = NULL; adjacent_face = NULL; 
	next = NULL; prev = NULL; twin = NULL;
}
