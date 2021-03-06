#include "Header Files\Blob.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\matrix\src\Vectors.h"
#include "Dependencies\matrix\src\Matrices.h"

// Poor man's approximation of PI
#define PI 3.1415926535898

bool bgenerated = false;
bool egenerated = false;

int numBBpointsLoop = 2 * PI / (PI / 6) + 1;
const int numbbPoints = numBBpointsLoop * 4 + 1;
Vector3* bbPoints = new Vector3[numbbPoints];
Vector3* bbPointColours = new Vector3[numbbPoints];

float astep = (PI) / (float)12;
float bstep = (PI) / (float)12;
int numBlobPoints = ((PI + 0.0001) / astep + 1)*((2 * PI + 0.0001) / bstep + 1) * 2;
Vector3* elipPoints = new Vector3[numBlobPoints];

int innerEnd = 0;
int midEnd = 0;

using namespace std;

Blob::Blob() {
	this->centre = { 0.0, 0.0, 0.0 };
	this->radius = 0.5;
	this->r = 1.0;
	this->g = 1.0;
	this->b = 1.0;
	this->lightSource = { 0.0, 0.0, 0.0 };
}

Blob::Blob(Vector3 centreN, float radius, Vector3 lightSourceN, Vector3 viewer) {
	this->centre = centreN;
	this->radius = radius;
	this->viewer = viewer;
	this->r = 1.0f;
	this->g = 1.0f;
	this->b = 1.0f;
	this->lightSource = lightSourceN;
	for (int i = 0; i < numbbPoints; i++) {
		bbPointColours[i] = Vector3(1.0f, 1.0f, 1.0f);
	}
}

void Blob::draw() {
		//if (!bgenerated) 
		genBillboard();
		rotToViewer();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);
		// Inner loop
		for (int i = 1; i < numBBpointsLoop; i++) {
			glColor3f(bbPointColours[0].x, bbPointColours[0].y, bbPointColours[0].z);
			glVertex3f(centre.x, centre.y, centre.z);
			glColor3f(bbPointColours[i].x, bbPointColours[i].y, bbPointColours[i].z);
			glVertex3f(bbPoints[i].x, bbPoints[i].y, bbPoints[i].z);
			glColor3f(bbPointColours[i+1].x, bbPointColours[i+1].y, bbPointColours[i+1].z);
			glVertex3f(bbPoints[i+1].x, bbPoints[i+1].y, bbPoints[i+1].z);
		}
		glColor3f(bbPointColours[0].x, bbPointColours[0].y, bbPointColours[0].z);
		glVertex3f(centre.x, centre.y, centre.z);
		glColor3f(bbPointColours[numBBpointsLoop].x, bbPointColours[numBBpointsLoop].y, bbPointColours[numBBpointsLoop].z);
		glVertex3f(bbPoints[numBBpointsLoop].x, bbPoints[numBBpointsLoop].y, bbPoints[numBBpointsLoop].z);
		glColor3f(bbPointColours[1].x, bbPointColours[1].y, bbPointColours[1].z);
		glVertex3f(bbPoints[1].x, bbPoints[1].y, bbPoints[1].z);		
		
		// Middle loop
		glVertex3f(bbPoints[1].x, bbPoints[1].y, bbPoints[1].z);
		glColor3f(bbPointColours[numBBpointsLoop * 2].x, bbPointColours[numBBpointsLoop * 2].y, bbPointColours[numBBpointsLoop * 2].z);
		glVertex3f(bbPoints[numBBpointsLoop * 2].x, bbPoints[numBBpointsLoop * 2].y, bbPoints[numBBpointsLoop * 2].z);
		glColor3f(bbPointColours[numBBpointsLoop + 1].x, bbPointColours[numBBpointsLoop + 1].y, bbPointColours[numBBpointsLoop + 1].z);
		glVertex3f(bbPoints[numBBpointsLoop + 1].x, bbPoints[numBBpointsLoop + 1].y, bbPoints[numBBpointsLoop + 1].z);
		for (int i = 2; i <= numBBpointsLoop; i++) {
			// Outer triangle
			glColor3f(bbPointColours[i].x, bbPointColours[i].y, bbPointColours[i].z);
			glVertex3f(bbPoints[i].x, bbPoints[i].y, bbPoints[i].z);
			glColor3f(bbPointColours[i + numBBpointsLoop - 1].x, bbPointColours[i + numBBpointsLoop - 1].y, bbPointColours[i + numBBpointsLoop - 1].z);
			glVertex3f(bbPoints[i + numBBpointsLoop - 1].x, bbPoints[i + numBBpointsLoop - 1].y, bbPoints[i + numBBpointsLoop - 1].z);
			glColor3f(bbPointColours[i + numBBpointsLoop].x, bbPointColours[i + numBBpointsLoop].y, bbPointColours[i + numBBpointsLoop].z);
			glVertex3f(bbPoints[i + numBBpointsLoop].x, bbPoints[i + numBBpointsLoop].y, bbPoints[i + numBBpointsLoop].z);
			// Inner triangle
			glColor3f(bbPointColours[i].x, bbPointColours[i].y, bbPointColours[i].z);
			glVertex3f(bbPoints[i].x, bbPoints[i].y, bbPoints[i].z);
			glColor3f(bbPointColours[i-1].x, bbPointColours[i-1].y, bbPointColours[i-1].z);
			glVertex3f(bbPoints[i-1].x, bbPoints[i-1].y, bbPoints[i-1].z);
			glColor3f(bbPointColours[i + numBBpointsLoop - 1].x, bbPointColours[i + numBBpointsLoop - 1].y, bbPointColours[i + numBBpointsLoop - 1].z);
			glVertex3f(bbPoints[i + numBBpointsLoop - 1].x, bbPoints[i + numBBpointsLoop - 1].y, bbPoints[i + numBBpointsLoop - 1].z);
		}
		glColor3f(bbPointColours[numBBpointsLoop].x, bbPointColours[numBBpointsLoop].y, bbPointColours[numBBpointsLoop].z);
		glVertex3f(bbPoints[numBBpointsLoop].x, bbPoints[numBBpointsLoop].y, bbPoints[numBBpointsLoop].z);
		glColor3f(bbPointColours[numBBpointsLoop * 2].x, bbPointColours[numBBpointsLoop * 2].y, bbPointColours[numBBpointsLoop * 2].z);
		glVertex3f(bbPoints[numBBpointsLoop * 2].x, bbPoints[numBBpointsLoop * 2].y, bbPoints[numBBpointsLoop * 2].z);
		glColor3f(bbPointColours[1].x, bbPointColours[1].y, bbPointColours[1].z);
		glVertex3f(bbPoints[1].x, bbPoints[1].y, bbPoints[1].z);

		// Outer Loop
		glColor3f(bbPointColours[25].x, bbPointColours[25].y, bbPointColours[25].z);
		glVertex3f(bbPoints[25].x, bbPoints[25].y, bbPoints[25].z);
		glColor3f(bbPointColours[26].x, bbPointColours[26].y, bbPointColours[26].z);
		glVertex3f(bbPoints[26].x, bbPoints[26].y, bbPoints[26].z);
		glColor3f(bbPointColours[27].x, bbPointColours[27].y, bbPointColours[27].z);
		glVertex3f(bbPoints[27].x, bbPoints[27].y, bbPoints[27].z);
		// Inner triangle
		for (int i = 15; i < 26; i++) {
			glColor3f(bbPointColours[i - 1].x, bbPointColours[i - 1].y, bbPointColours[i - 1].z);
			glVertex3f(bbPoints[i - 1].x, bbPoints[i - 1].y, bbPoints[i - 1].z);
			glColor3f(bbPointColours[i * 2 - 1].x, bbPointColours[i * 2 - 1].y, bbPointColours[i * 2 - 1].z);
			glVertex3f(bbPoints[i * 2 - 1].x, bbPoints[i * 2 - 1].y, bbPoints[i * 2 - 1].z);
			glColor3f(bbPointColours[i].x, bbPointColours[i].y, bbPointColours[i].z);
			glVertex3f(bbPoints[i].x, bbPoints[i].y, bbPoints[i].z);
		}
		// Outer triangles
		for (int i = 14; i < 26; i++) {
			glColor3f(bbPointColours[i].x, bbPointColours[i].y, bbPointColours[i].z);
			glVertex3f(bbPoints[i].x, bbPoints[i].y, bbPoints[i].z);
			glColor3f(bbPointColours[i * 2 + 1].x, bbPointColours[i * 2 + 1].y, bbPointColours[i * 2 + 1].z);
			glVertex3f(bbPoints[i * 2 + 1].x, bbPoints[i * 2 + 1].y, bbPoints[i * 2 + 1].z);
			glColor3f(bbPointColours[i * 2 + 2].x, bbPointColours[i * 2 + 2].y, bbPointColours[i * 2 + 2].z);
			glVertex3f(bbPoints[i * 2 + 2].x, bbPoints[i * 2 + 2].y, bbPoints[i * 2 + 2].z);
			
			glColor3f(bbPointColours[i].x, bbPointColours[i].y, bbPointColours[i].z);
			glVertex3f(bbPoints[i].x, bbPoints[i].y, bbPoints[i].z);
			glColor3f(bbPointColours[i * 2 + 2].x, bbPointColours[i * 2 + 2].y, bbPointColours[i * 2 + 2].z);
			glVertex3f(bbPoints[i * 2 + 2].x, bbPoints[i * 2 + 2].y, bbPoints[i * 2 + 2].z);
			glColor3f(bbPointColours[i * 2 - 1].x, bbPointColours[i * 2 - 1].y, bbPointColours[i * 2 - 1].z);
			glVertex3f(bbPoints[i * 2 - 1].x, bbPoints[i * 2 - 1].y, bbPoints[i * 2 - 1].z);
		}
		
		glEnd();

		//if (!egenerated) 
		//generateEllipse();

		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < numBlobPoints; i++) {
			glColor3f(1.0, 0, 0);
			glVertex3f(elipPoints[i].x, elipPoints[i].y, elipPoints[i].z);
		}
		glEnd();
		cout << "Blob: Blob drawn" << endl;*/
}

void Blob::genBillboard() {
	int n = 0;
	bbPoints[n] = centre;
	n++;
	// Inner Loop
	for (float i = 2 * PI; i > 0; i -= PI / 6) {
		bbPoints[n].x = cos(i) * radius / 3;
		bbPoints[n].y = sin(i) * radius / 3;
		bbPoints[n].z = 0;
		//bbPoints[n] = rot * bbPoints[n];
		bbPoints[n] += centre;
		n++;
	}
	// Middle Loop
	for (float i = 2 * PI; i > 0; i -= PI / 6) {
		bbPoints[n].x = cos(i - PI / 12) * radius * 2 / 3;
		bbPoints[n].y = sin(i - PI / 12) * radius * 2 / 3;
		bbPoints[n].z = 0;
		//bbPoints[n] = rot * bbPoints[n];
		bbPoints[n] += centre;
		n++;
	}
	// Outer Loop
	for (float i = 2 * PI; i > 0; i -= PI / 6) {
		bbPoints[n].x = cos(i) * radius;
		bbPoints[n].y = sin(i) * radius;
		bbPoints[n].z = 0;
		//bbPoints[n] = rot * bbPoints[n];
		bbPoints[n] += centre;
		n++;
		bbPoints[n].x = cos(i + PI / 12) * radius;
		bbPoints[n].y = sin(i + PI / 12) * radius;
		bbPoints[n].z = 0;
		//bbPoints[n] = rot * bbPoints[n];
		bbPoints[n] += centre;
		n++;
	}
	bgenerated = true;
}

Matrix3 Blob::calcRotMatrix(Vector3 a, Vector3 b) {
	float dot = a.dot(b);
	float crossab = a.cross(b).length();
	Vector3 unit = (b - (a.dot(b))*a) / (b - (a.dot(b))*a).length();
	Vector3 crossba = b.cross(a);

	Matrix3 gg = { dot, crossab, 0, -crossab, dot, 0, 0, 0, 1};
	Matrix3 ffi = { a.x, a.y, a.z, unit.x, unit.y, unit.z, crossba.x, crossba.y, crossba.z};

	//Matrix4 transf = { 1,0,0,centre.x,0,1,0,centre.y,0,0,1,centre.z,0,0,0,1 };
	//Matrix4 transfback = { 1,0,0,-centre.x,0,1,0,-centre.y,0,0,1,-centre.z,0,0,0,1 };

	Matrix3 ffiinv = inverse(ffi);
	Matrix3 rot = ffi * gg * ffiinv;
	return rot;
}

/*Matrix4 Blob::inverse(Matrix4 m) {
	if (m[3] == 0 && m[7] == 0 && m[11] == 0 && m[15] == 1) {
		Matrix3 r(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
		r = invert(r);
		m[0] = r[0];  m[1] = r[1];  m[2] = r[2];
		m[4] = r[3];  m[5] = r[4];  m[6] = r[5];
		m[8] = r[6];  m[9] = r[7];  m[10] = r[8];

		// -R^-1 * T
		float x = m[12];
		float y = m[13];
		float z = m[14];
		m[12] = -(r[0] * x + r[3] * y + r[6] * z);
		m[13] = -(r[1] * x + r[4] * y + r[7] * z);
		m[14] = -(r[2] * x + r[5] * y + r[8] * z);
	}
	else {
		// get cofactors of minor matrices
		float cofactor0 = getCofactor(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]);
		float cofactor1 = getCofactor(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]);
		float cofactor2 = getCofactor(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]);
		float cofactor3 = getCofactor(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);

		// get determinant
		float determinant = m[0] * cofactor0 - m[1] * cofactor1 + m[2] * cofactor2 - m[3] * cofactor3;
		float EPSILON = 0.00001f;
		if (fabs(determinant) <= EPSILON) {
			Matrix4 id = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
			return id; // cannot inverse, make it idenety matrix
		}

		// get rest of cofactors for adj(M)
		float cofactor4 = getCofactor(m[1], m[2], m[3], m[9], m[10], m[11], m[13], m[14], m[15]);
		float cofactor5 = getCofactor(m[0], m[2], m[3], m[8], m[10], m[11], m[12], m[14], m[15]);
		float cofactor6 = getCofactor(m[0], m[1], m[3], m[8], m[9], m[11], m[12], m[13], m[15]);
		float cofactor7 = getCofactor(m[0], m[1], m[2], m[8], m[9], m[10], m[12], m[13], m[14]);

		float cofactor8 = getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[13], m[14], m[15]);
		float cofactor9 = getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[12], m[14], m[15]);
		float cofactor10 = getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[12], m[13], m[15]);
		float cofactor11 = getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[12], m[13], m[14]);

		float cofactor12 = getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[9], m[10], m[11]);
		float cofactor13 = getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[8], m[10], m[11]);
		float cofactor14 = getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[8], m[9], m[11]);
		float cofactor15 = getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);

		// build inverse matrix = adj(M) / det(M)
		// adjugate of M is the transpose of the cofactor matrix of M
		float invDeterminant = 1.0f / determinant;
		m[0] = invDeterminant * cofactor0;
		m[1] = -invDeterminant * cofactor4;
		m[2] = invDeterminant * cofactor8;
		m[3] = -invDeterminant * cofactor12;

		m[4] = -invDeterminant * cofactor1;
		m[5] = invDeterminant * cofactor5;
		m[6] = -invDeterminant * cofactor9;
		m[7] = invDeterminant * cofactor13;

		m[8] = invDeterminant * cofactor2;
		m[9] = -invDeterminant * cofactor6;
		m[10] = invDeterminant * cofactor10;
		m[11] = -invDeterminant * cofactor14;

		m[12] = -invDeterminant * cofactor3;
		m[13] = invDeterminant * cofactor7;
		m[14] = -invDeterminant * cofactor11;
		m[15] = invDeterminant * cofactor15;
	}

	return m;
}*/

Matrix3 Blob::inverse(Matrix3 m) {
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

/*float Blob::getCofactor(float m0, float m1, float m2,
	float m3, float m4, float m5,
	float m6, float m7, float m8)
{
	return m0 * (m4 * m8 - m5 * m7) -
		m1 * (m3 * m8 - m5 * m6) +
		m2 * (m3 * m7 - m4 * m6);
}*/

void Blob::generateEllipse() {
	int i = 0;
	for (float t = -PI / 2; t <= (PI / 2) + .0001; t += astep)
	{
		for (float s = -PI; s <= PI + .0001; s += bstep) {
			elipPoints[i].x = radius * cos(t) * cos(s) + centre.x;
			elipPoints[i].y = radius * cos(t) * sin(s) + centre.y;
			elipPoints[i].z = radius * sin(t) + centre.z;
			i++;
			elipPoints[i].x = radius * cos(t + astep) * cos(s) + centre.x;
			elipPoints[i].y = radius * cos(t + astep) * sin(s) + centre.y;
			elipPoints[i].z = radius * sin(t + astep) + centre.z;
			i++;
		}
	}
	cout << "generated around: " << centre << endl;
	egenerated = true;
}

Vector3 Blob::getColour() {
	return Vector3(r, g, b);
}
void Blob::setColour(float rN, float gN, float bN) {
	this->r = rN; 
	this->g = gN;
	this->b = bN;
	cout << "Blob: set colour " << Vector3{ r, g, b } << endl;
}

Vector3 Blob::getPoint(int index) {
	return bbPoints[index];
}
void Blob::setPointColour(int index, float rn, float gn, float bn) {
	bbPointColours[index] = Vector3(rn, gn, bn);
}
Vector3 Blob::getPointColour(int index) {
	return bbPointColours[index];
}

Vector3 Blob::getCentre() {
	return centre;
}
float Blob::getRadius() {
	return this->radius;
}
int Blob::getNumbbPoints() {
	return numbbPoints;
}


void Blob::rotToViewer() {
	Vector3 A = (centre - lightSource).normalize();
	Vector3 B = (centre - viewer).normalize();
	Matrix3 rotViewer = calcRotMatrix(A, B);
	cout << "Should be zero - " << B - rotViewer * A << endl;

	for (int i = 0; i < numbbPoints; i++) {
		bbPoints[i] -= centre;
		bbPoints[i] = rotViewer * bbPoints[i];
		bbPoints[i] += centre;
	}
}

void Blob::sunflower() {
	genBillboard();
	Vector3 A = { 0, 0, 1 };
	Vector3 B = (centre - lightSource).normalize();
	Matrix3 rot = calcRotMatrix(A, B);
	//cout << "Should be zero - " << B - rot * A << endl;

	for (int i = 0; i < numbbPoints; i++) {
		bbPoints[i] -= centre;
		bbPoints[i] = rot * bbPoints[i];
		bbPoints[i] += centre;
	}
}

Blob::~Blob()
{
}
