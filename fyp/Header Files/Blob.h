#pragma once
#include "Dependencies\matrix\src\Matrices.h"
#include "Dependencies\matrix\src\Vectors.h"
class Blob
{
public:
	Blob();
	Blob(Vector3 centre, float radius, Vector3 lightSource, Vector3 viewer);
	void draw();
	void genBillboard();
	Vector3 getColour();
	void setColour(float rN, float gN, float bN);
	Vector3 getPoint(int index);
	Vector3 getPointColour(int index);
	void setPointColour(int index, float rN, float gN, float bN);
	Vector3 getCentre();
	float getRadius();
	int getNumbbPoints();
	void rotToViewer();
	void sunflower();
	~Blob();
private:
	float r, g, b, radius;
	Vector3 lightSource, centre, viewer;
	void generateEllipse();
	Matrix3 calcRotMatrix(Vector3 a, Vector3 b);
	Matrix3 inverse(Matrix3 m);
	//Matrix4 inverse(Matrix4 m);
	/*float getCofactor(float m0, float m1, float m2,
		float m3, float m4, float m5,
		float m6, float m7, float m8);*/
};

