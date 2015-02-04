#include "StdAfx.h"
#include "myMesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <GL/glew.h>
#include "myvector3d.h"

myMesh::myMesh(void) {
	vertices.clear();
	faces.clear();
	halfedges.clear();
}

myMesh::~myMesh(void) {

}

void myMesh::checkMesh() {

}

myHalfedge* myMesh::getTwin(map<pair<int, int>, myHalfedge *> &table, int &a, int &b, myHalfedge *value) {
	pair<int, int> points = make_pair(a, b);
	map<pair<int, int>, myHalfedge *>::iterator it = table.find(points);
	myHalfedge *twin;

	if (it == table.end()) { // This means there was no myHalfedge * present at location(a, b).
		// [twin a, b] doesn't exist, check if the [twin b, a] exists
		points = make_pair(b, a);
		it = table.find(points);
		if (it == table.end()) { // [twin b, a] doesn't exist either
			table[points] = value;
		}
	}
	else { // [twin of a, b exists]
		twin = it->second;
		twin->twin = value;
		return twin;
	}
	return NULL;
}

void myMesh::readFile(std::string filename) {
	string s, t;
	string tmp;
	double x, y, z;
	int index; // vertex index in the face
	map<pair<int, int>, myHalfedge *> table;

	ifstream fin(filename);
	if (!fin.is_open())
		cout << "Unable to open file!\n";

	while (getline(fin, s)) {
		stringstream myline(s);
		myline >> t;
		if (t == "v") // Vertex
		{
			myline >> tmp; // vertex: x coordinate
			x = std::stod(tmp);

			myline >> tmp; // vertex: y coordinate
			y = std::stod(tmp);

			myline >> tmp; // vertex: z coordinate
			z = std::stod(tmp);

			myVertex *vertex = new myVertex(new myPoint3D(x, y, z));
			vertices.push_back(vertex);
		}
		else if (t == "f") // Face
		{
			faces.push_back(new myFace());

			for (int i = 0; i < 3; i++) {
				halfedges.push_back(new myHalfedge());
			}

			int lastFaceIndex = faces.size() - 1;
			int firstHalfEdgeIndex = halfedges.size() - 3;
			int currentHalfEdgeIndex = firstHalfEdgeIndex;
			int nextIndex;
			faces[lastFaceIndex]->adjacent_halfedge = halfedges[halfedges.size() - 1];

			int i = 0;
			int vertices_visited[3];
			while (myline >> tmp) // loops 3 times (apple.obj)
			{
				index = std::stoi(tmp) - 1;
				vertices_visited[i++] = index;

				vertices[index]->originof = halfedges[currentHalfEdgeIndex];

				halfedges[currentHalfEdgeIndex]->adjacent_face = faces[lastFaceIndex];

				halfedges[currentHalfEdgeIndex]->next = halfedges[((currentHalfEdgeIndex + 1) % 3) + firstHalfEdgeIndex];
				halfedges[currentHalfEdgeIndex]->prev = halfedges[(currentHalfEdgeIndex - 1 + 3) % 3 + firstHalfEdgeIndex];

				halfedges[currentHalfEdgeIndex]->source = vertices[index];
				currentHalfEdgeIndex++;
			}
			
			// loop through the last used vertices and set their twins
			int j = firstHalfEdgeIndex;
			for (int i = 0; i < 3; i++) {
				halfedges[j]->twin = getTwin(table, vertices_visited[i], vertices_visited[(i+1)%3], halfedges[j]);
				j++;
			}
		}
	}
	checkMesh();
	//normalize();
}

void myMesh::computeNormals() {
	for (vector<myFace *>::iterator it = faces.begin(); it != faces.end(); it++)
		(*it)->computeNormal();

	for (vector<myVertex *>::iterator it = vertices.begin(); it != vertices.end(); it++)
		(*it)->computeNormal();
}

void myMesh::normalize() {
	int i;
	int tmpxmin = 0, tmpymin = 0, tmpzmin = 0, tmpxmax = 0, tmpymax = 0, tmpzmax = 0;

	for (i = 0; i < vertices.size(); i++) {
		if (vertices[i]->point->X < vertices[tmpxmin]->point->X) tmpxmin = i;
		if (vertices[i]->point->X > vertices[tmpxmax]->point->X) tmpxmax = i;

		if (vertices[i]->point->Y < vertices[tmpymin]->point->Y) tmpymin = i;
		if (vertices[i]->point->Y > vertices[tmpymax]->point->Y) tmpymax = i;

		if (vertices[i]->point->Z < vertices[tmpzmin]->point->Z) tmpzmin = i;
		if (vertices[i]->point->Z > vertices[tmpzmax]->point->Z) tmpzmax = i;
	}

	double xmin = vertices[tmpxmin]->point->X, xmax = vertices[tmpxmax]->point->X,
		ymin = vertices[tmpymin]->point->Y, ymax = vertices[tmpymax]->point->Y,
		zmin = vertices[tmpzmin]->point->Z, zmax = vertices[tmpzmax]->point->Z;

	double scale = (xmax - xmin) > (ymax - ymin) ? (xmax - xmin) : (ymax - ymin);
	scale = scale > (zmax - zmin) ? scale : (zmax - zmin);

	for (i = 0; i < vertices.size(); i++) {
		vertices[i]->point->X -= (xmax + xmin) / 2;
		vertices[i]->point->Y -= (ymax + ymin) / 2;
		vertices[i]->point->Z -= (zmax + zmin) / 2;

		vertices[i]->point->X /= scale;
		vertices[i]->point->Y /= scale;
		vertices[i]->point->Z /= scale;
	}
}