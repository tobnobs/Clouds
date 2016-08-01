#pragma once
#include "Dependencies\matrix\src\Matrices.h"
#include "Dependencies\matrix\src\Vectors.h"
class BlobS
{
public:
	BlobS();
	BlobS(Vector3 centre, float radius, Vector3 viewer);
	void draw();
	void genBillboard();
	Vector3 getColour();
	void setColour(float rN, float gN, float bN);
	Vector3 getCentre();
	float getRadius();
	void rotToViewer();
	~BlobS();
private:
	float r, g, b, radius;
	Vector3 centre, viewer;
	Matrix3 calcRotMatrix(Vector3 a, Vector3 b);
	Matrix3 inverse(Matrix3 m);
};

