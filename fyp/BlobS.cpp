#include "Header Files\BlobS.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\matrix\src\Vectors.h"
#include "Dependencies\matrix\src\Matrices.h"

// Poor man's approximation of PI
#define PI 3.1415926535898

int numbbPointsS = 2 * PI / (PI / 6) + 2;
Vector3* bbPointsS = new Vector3[numbbPointsS];

using namespace std;

BlobS::BlobS() {
	this->centre = { 0.0, 0.0, 0.0 };
	this->radius = 0.5;
	this->r = 1.0;
	this->g = 1.0;
	this->b = 1.0;
}

BlobS::BlobS(Vector3 centreN, float radius, Vector3 viewer) {
	this->centre = centreN;
	this->radius = radius;
	this->viewer = viewer;
	this->r = 1.0f;
	this->g = 1.0f;
	this->b = 1.0f;
}

void BlobS::draw() {
	genBillboard();
	rotToViewer();
	glColor3f(r, g, b);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < numbbPointsS; i++) {
		glVertex3f(bbPointsS[i].x, bbPointsS[i].y, bbPointsS[i].z);
	}
	glEnd();
}

void BlobS::genBillboard() {
	int n = 0;
	bbPointsS[n] = centre;
	n++;
	for (float i = 2 * PI; i > 0; i -= PI / 6) {
		bbPointsS[n].x = cos(i) * radius;
		bbPointsS[n].y = sin(i) * radius;
		bbPointsS[n].z = 0;
		//bbPointsS[n] = rot * bbPointsS[n];
		bbPointsS[n] += centre;
		n++;
	}
}

Matrix3 BlobS::calcRotMatrix(Vector3 a, Vector3 b) {
	float dot = a.dot(b);
	float crossab = a.cross(b).length();
	Vector3 unit = (b - (a.dot(b))*a) / (b - (a.dot(b))*a).length();
	Vector3 crossba = b.cross(a);

	Matrix3 gg = { dot, crossab, 0, -crossab, dot, 0, 0, 0, 1 };
	Matrix3 ffi = { a.x, a.y, a.z, unit.x, unit.y, unit.z, crossba.x, crossba.y, crossba.z };

	Matrix3 ffiinv = inverse(ffi);
	Matrix3 rot = ffi * gg * ffiinv;
	return rot;
}

Matrix3 BlobS::inverse(Matrix3 m) {
	float determinant, invDeterminant;
	float tmp[9];

	tmp[0] = m[4] * m[8] - m[5] * m[7];
	tmp[1] = m[2] * m[7] - m[1] * m[8];
	tmp[2] = m[1] * m[5] - m[2] * m[4];
	tmp[3] = m[5] * m[6] - m[3] * m[8];
	tmp[4] = m[0] * m[8] - m[2] * m[6];
	tmp[5] = m[2] * m[3] - m[0] * m[5];
	tmp[6] = m[3] * m[7] - m[4] * m[6];
	tmp[7] = m[1] * m[6] - m[0] * m[7];
	tmp[8] = m[0] * m[4] - m[1] * m[3];

	// check determinant if it is 0
	determinant = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
	float EPSILON = 0.00001f;
	if (fabs(determinant) <= EPSILON) {
		Matrix3 id = { 1,0,0,0,1,0,0,0,1 };
		return id; // cannot inverse, make it idenety matrix
	}

	// divide by the determinant
	invDeterminant = 1.0f / determinant;
	m[0] = invDeterminant * tmp[0];
	m[1] = invDeterminant * tmp[1];
	m[2] = invDeterminant * tmp[2];
	m[3] = invDeterminant * tmp[3];
	m[4] = invDeterminant * tmp[4];
	m[5] = invDeterminant * tmp[5];
	m[6] = invDeterminant * tmp[6];
	m[7] = invDeterminant * tmp[7];
	m[8] = invDeterminant * tmp[8];

	return m;
}

Vector3 BlobS::getColour() {
	return Vector3(r, g, b);
}
void BlobS::setColour(float rN, float gN, float bN) {
	this->r = rN;
	this->g = gN;
	this->b = bN;
	//cout << "Blob: set colour " << Vector3{ r, g, b } << endl;
}

Vector3 BlobS::getCentre() {
	return centre;
}
float BlobS::getRadius() {
	return this->radius;
}

void BlobS::rotToViewer() {
	Vector3 A = { 0,0,1 };// (centre - lightSource).normalize();
	Vector3 B = (centre - viewer).normalize();
	Matrix3 rotViewer = calcRotMatrix(A, B);
	//cout << "Should be zero - " << B - rotViewer * A << endl;

	for (int i = 0; i < numbbPointsS; i++) {
		bbPointsS[i] -= centre;
		bbPointsS[i] = rotViewer * bbPointsS[i];
		bbPointsS[i] += centre;
	}
}

BlobS::~BlobS()
{
}
