#pragma once
#include "myFace.h"
#include "myHalfedge.h"
#include "myVertex.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

class myMesh
{
public:
	std::vector<myVertex *> vertices;
	std::vector<myHalfedge *> halfedges;
	std::vector<myFace *> faces;
	std::string name;

	void checkMesh();
	void readFile(std::string filename);
	void computeNormals();
	void normalize();

	myHalfedge* getTwin(map<pair<int, int>, myHalfedge *> &table, int &a, int &b, myHalfedge *value);

	myMesh(void);
	~myMesh(void);
};

