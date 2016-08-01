#include "Header Files\Builder.h"
#include "Header Files\Blob.h"
#include "Header Files\BlobS.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\matrix\src\Matrices.h"
#include "Dependencies\matrix\src\Vectors.h"
#include <math.h>
//#include <iostream>
//#include <algorithm>

using namespace std;

// Poor man's approximation of PI
#define PI 3.1415926535898
// Degrees to radians
#define DTOR (PI / 180.0f)
// Time to angle
#define TTOA (360/24)

// DOME PROPERTIES
// Intervals between verticies.
int dtheta = 5;
int dphi = 5;
float domeRadius = 7.0;
// The number of verticies which will fit on a sphere with dtheta and dphi
int numDomePoints = (int)((360 / dtheta)*(90 / dphi) * 4);

// CLOUD PROPERTIES
// The number of particles in the cloud
int NumParticles = 0;
// metaballs
bool bbgen = false;
float tStep = (PI) / (float)12;
float sStep = (PI) / (float)12;
BlobS* blobs;
Blob* blobMultiPoint;
Vector3* centres;

// TOTAL VERTICES
Vector4* DomePoints = new Vector4[numDomePoints];
Vector4* CloudPoints = new Vector4[NumParticles];


Builder::Builder(Vector3 centres[], int numBlobs, float radius[], float time, Vector3 observer, float density, bool skyLight) {
	this->numBlobs = numBlobs;
	blobs = new BlobS[numBlobs];
	this->centres = centres;
	this->lightColour = calcLightColour(time);
	this->blueVal = lightColour.z;
	this->lightSource = Vector3(0.0, sin(time*TTOA) * 10, -cos(time*TTOA) * 10);
	this->viewer = observer;
	this->density = density;
	this->ambient = 0.05;
	this->skyLight = skyLight;
	domeGen = false;
	cloudGen = false;
	for (int i = 0; i < numBlobs; i++) {
		blobs[i] = BlobS(centres[i], radius[i], viewer);
	};
	shadeCloudSimple();
	drawDome();
}


void Builder::generateDome() {
	//int theta, phi;

	int n = 0;	// Iterator through the list of verticies.

				// Fill vertices
	for (int phi = 0; phi <= 90 - dphi; phi += (int)dphi) {
		for (int theta = 0; theta <= 360 - dtheta; theta += (int)dtheta) {
			// Calculate the vector at phi, theta
			DomePoints[n].x = domeRadius * sinf(phi*DTOR) * cosf(DTOR*theta);
			DomePoints[n].y = domeRadius * sinf(phi*DTOR) * sinf(DTOR*theta);
			DomePoints[n].z = domeRadius * cosf(phi*DTOR);

			n++;

			// Calculate the vector at phi+dphi, theta
			DomePoints[n].x = domeRadius * sinf((phi + dphi)*DTOR) * cosf(theta*DTOR);
			DomePoints[n].y = domeRadius * sinf((phi + dphi)*DTOR) * sinf(theta*DTOR);
			DomePoints[n].z = domeRadius * cosf((phi + dphi)*DTOR);

			n++;

			// Calculate the vector at phi, theta+dtheta
			DomePoints[n].x = domeRadius * sinf(DTOR*phi) * cosf(DTOR*(theta + dtheta));
			DomePoints[n].y = domeRadius * sinf(DTOR*phi) * sinf(DTOR*(theta + dtheta));
			DomePoints[n].z = domeRadius * cosf(DTOR*phi);

			n++;

			if (phi > -90 && phi < 90) {
				// Calculate the vector at phi+dphi, theta+dtheta
				DomePoints[n].x = domeRadius * sinf((phi + dphi)*DTOR) * cosf(DTOR*(theta + dtheta));
				DomePoints[n].y = domeRadius * sinf((phi + dphi)*DTOR) * sinf(DTOR*(theta + dtheta));
				DomePoints[n].z = domeRadius * cosf((phi + dphi)*DTOR);

				n++;
			}
			if (n > numDomePoints) {
				cout << "Error: too many dome points \n";
			}
		}
	}
	domeGen = 1;
}
void Builder::drawDome() {
	if (!domeGen) generateDome();
	domeGen = true;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Outer Dome
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numDomePoints; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(DomePoints[i].x, DomePoints[i].y, DomePoints[i].z - 1.99);
	}
	glEnd();

	float bVal = 0.72 * blueVal;

	// Inner Dome
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numDomePoints; i++) {
		// Colour depending on angle from horizon
		float rgVal = (-DomePoints[i].z / (domeRadius * 5) + 0.5) * lightColour.y;
		glColor3f(rgVal, rgVal, bVal);
		if (DomePoints[i].x > lightSource.x - 0.3 && DomePoints[i].x < lightSource.x + 0.3
			&& DomePoints[i].x > lightSource.y - 0.3 && DomePoints[i].y < lightSource.x + 0.3
			&& DomePoints[i].x > lightSource.z - 0.3 && DomePoints[i].z < lightSource.x + 0.3) {
			glColor3f((lightColour.x + rgVal) / 2, (lightColour.y + rgVal) / 2, (lightColour.z + bVal) / 2);
		}
		glVertex3f(DomePoints[i].x, DomePoints[i].y, DomePoints[i].z - 2.0);
	}
	glEnd();
}

void Builder::generateCloud() {
	srand(time(NULL));

	float phimax = PI;
	float phimin = -PI;
	float thetamax = PI;
	float thetamin = -PI;

	for (int i = 0; i < (NumParticles / 3); i++) {
		float phi = phimin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (phimax - phimin)));
		float theta = thetamin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (thetamax - thetamin)));
		CloudPoints[i].x = cos(phi) * cos(theta) *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 - 0))));
		CloudPoints[i].y = cos(phi) * sin(theta) *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 - 0))));
		CloudPoints[i].z = 0.3 + sin(phi) *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2 - 0))));
	}
	for (int i = (NumParticles / 3); i < (2 * NumParticles / 3); i++) {
		float phi = phimin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (phimax - phimin)));
		float theta = thetamin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (thetamax - thetamin)));
		CloudPoints[i].x = 0.3 + cos(phi) * cos(theta) * 1.2 *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 - 0))));
		CloudPoints[i].y = 0.4 + cos(phi) * sin(theta) * 1.2 *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 - 0))));
		CloudPoints[i].z = 0.33 + sin(phi) * 0.7 *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2 - 0))));
	}
	for (int i = (2 * NumParticles / 3); i < NumParticles; i++) {
		float phi = phimin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (phimax - phimin)));
		float theta = thetamin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (thetamax - thetamin)));
		CloudPoints[i].x = 0.3 + cos(phi) * cos(theta) *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 - 0))));
		CloudPoints[i].y = 0.2 + cos(phi) * sin(theta) *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 - 0))));
		CloudPoints[i].z = 0.3 + sin(phi) *
			(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2 - 0))));
	}
	cloudGen = true;
}
void Builder::drawCloud() {
	if (!cloudGen) generateCloud();

	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	for (int i = 0; i < NumParticles; i++) {
		glVertex3f(CloudPoints[i].x, CloudPoints[i].y, CloudPoints[i].z);
	}
	glEnd();
}

//Setting the colour of the light according to the time of day
Vector3 Builder::calcLightColour(float time) {
	float red, green, blue;
	if (time < 7.0) {
		if (time < 6.0) {
			green = (-cos((time - 5.0) * 90) + 1) / 3;
		}
		else green = 1.0;
		if (time < 5.0) {
			red = (-cos((time - 5.0) * 180) + 1) / 3;
		}
		else red = 1.0;
		blue = (-cos((time - 5.0) * 60) + 1) / 3;
		if (time < 4.0) {
			red = 0.0;
			green = 0.0;
			blue = 0.0;
		}
	}
	else if (time > 19) {
		if (time < 20.0) {
			blue = (cos((time - 19.0) * 90) + 1) / 3 + 0.1;
		}
		else blue = 0.05;
		if (time < 21.0) {
			green = (cos((time - 19.0) * 90) + 1) / 4 + 0.1;
		}
		else green = 0.05;
		red = (cos((time - 19.0) * 60) + 1) / 3 + 0.1;
		if (time > 22.0) {
			red = 0.0;
			green = 0.0;
			blue = 0.0;
		}
	}
	else {
		red = 1.0;
		green = 1.0;
		blue = 1.0;
	}
	return Vector3(red, green, blue);
}
Vector3 Builder::getLightColour() {
	return this->lightColour;
}

// Multiple colour billboards
void Builder::lightMetas() {
	// For every blob
	for (int i = 0; i < numBlobs; i++) {
		// Rotate it towards the sun
		blobMultiPoint[i].sunflower();
		// For every point in that blob
		int numPoints = blobMultiPoint[i].getNumbbPoints();
		for (int k = 0; k < numPoints; k++) {
			// select the point
			Vector3 iPoint = blobMultiPoint[i].getPoint(k);
			// Vector from the sun to the point
			Vector3 a = lightSource - iPoint;
			// Initial brightness
			float brightness = 1;
			// For every blob closer to the sun
			for (int j = 0; j < numBlobs; j++) {
				if (a.length() > (lightSource - blobMultiPoint[j].getCentre()).length()) {
					// Vector from the centre of blob j to the point
					Vector3 b = blobMultiPoint[j].getCentre() - iPoint;
					// Distance from the vector to the centre of the blob
					float d = (a.cross(b)).length() / a.length();
					float rad = blobMultiPoint[j].getRadius();
					// If the distance is smaller than the radius of the blob
					if (d > rad) {
						// Subtract from the brightness according to intersection
						brightness -= gaussian(d, 0.3f, 2 * rad);
					}
				}
			}
			// Make sure brightness isn't negative
			if (brightness < 0) brightness = 0;
			// Multiply the brightness ( < 1 ) by the colour of the original light
			Vector3 pointColour = brightness * lightColour;
			// Add some ambient light
			pointColour = pointColour + Vector3(0.3, 0.3, 0.3);
			// Make sure its not above 1
			if (pointColour.x > 1) pointColour.x = 1.0f;
			if (pointColour.y > 1) pointColour.y = 1.0f;
			if (pointColour.z > 1) pointColour.z = 1.0f;
			cout << "pointColour = " << pointColour << endl;
			// Set the new colour
			blobMultiPoint[i].setPointColour(k, pointColour.x, pointColour.y, pointColour.z);
			// Check its not too dark
			if (blobMultiPoint[i].getPointColour(k).x < 0.3 
					&& blobMultiPoint[i].getPointColour(k).y < 0.3 
					&& blobMultiPoint[i].getPointColour(k).z < 0.3)
				cout << "Too dark, point " << i << endl;
		}
	}
}
// Multiple colour billboards
void Builder::lightMetasSky() {
	//For every blob
	for (int i = 0; i < numBlobs; i++) {
		// Rotate to face the viewer
		blobMultiPoint[i].rotToViewer();
		// For every point in that blob
		int kmax = blobMultiPoint[i].getNumbbPoints();
		for (int k = 0; k < kmax; k++) {
			// select the point
			Vector3 iPoint = blobMultiPoint[i].getPoint(k);
			// Vector from observer to the point
			Vector3 a = viewer - iPoint;
			// Initial brightness
			float brightness = 1;
			// For every blob that isn't i
			for (int j = 0; j < numBlobs; j++) {
				// If that blob is further from the viewer
				if (a.length() < (blobMultiPoint[j].getCentre() - viewer).length()) {
					// Vector from the centre of blob j to the point
					Vector3 b = blobMultiPoint[j].getCentre() - iPoint;
					// Distance from the vector to the centre of the blob
					float d = (a.cross(b)).length() / a.length();
					float rad = blobMultiPoint[j].getRadius();
					// If the distance is smaller than the radius of the blob
					if (d > rad) {
						// Subtract from the brightness according to intersection
						brightness -= gaussian(d, 0.3f, 2 * rad);
					}
				}
			}
			// Make sure the brightness value isn't negative
			if (brightness < 0) brightness = 0;
			// Horizontal vector
			Vector3 hor = Vector3(a.x, a.y, 0);
			// Angle between horizontal and d
			float alt = (hor.dot(a)) / (hor.length() * a.length());
			if (alt < 0) alt = -alt;
			// Calculate colour of sky at intersection
			float bVal = 0.72 * brightness;
			float rgVal = alt / (domeRadius * 5) + 0.5 * brightness;
			// Set the new colour
			blobMultiPoint[i].setPointColour(k, rgVal * blobMultiPoint[i].getPointColour(k).x,
				rgVal * blobMultiPoint[i].getPointColour(k).y,
				bVal * blobMultiPoint[i].getPointColour(k).z);
		}
	}
}

//Single colour billboards
void Builder::lightMetaSimple() {
	// For every blob
	for (int i = 0; i < numBlobs; i++) {
		// Rotate it towards the sun
		//blobs[i].sunflower();
		// select the centre
		Vector3 iCentre = blobs[i].getCentre();
		// Vector from the sun to the point
		Vector3 a = lightSource - iCentre;
		// Initial brightness
		float brightness = 1;
		// For every blob closer to the sun
		for (int j = 0; j < numBlobs; j++) {
			if (a.length() > (lightSource - blobs[j].getCentre()).length()) {
				// Vector from the centre of blob j to the point
				Vector3 b = blobs[j].getCentre() - iCentre;
				// Distance from the vector to the centre of the blob
				float d = (a.cross(b)).length() / a.length();
				float rad = blobs[j].getRadius();
				// If the distance is smaller than the radius of the blob
				if (d > rad) {
					// Subtract from the brightness according to intersection
					brightness -= gaussian(d, density, 2 * rad);
				}
			}
		}
		// Make sure brightness isn't negative
		if (brightness < 0) brightness = 0;
		// Multiply the brightness ( < 1 ) by the colour of the original light
		Vector3 pointColour = brightness * lightColour;
		// Make sure its not above 1
		if (pointColour.x > 1) pointColour.x = 1.0f;
		if (pointColour.y > 1) pointColour.y = 1.0f;
		if (pointColour.z > 1) pointColour.z = 1.0f;
		// Set the new colour
		blobs[i].setColour(pointColour.x, pointColour.y, pointColour.z);
	}
}
//Single colour billboards
void Builder::lightMetasSkySimple() {
	//For every blob
	for (int i = 0; i < numBlobs; i++) {
		// Rotate to face the viewer
		blobs[i].rotToViewer();
		// select the centre
		Vector3 iCentre = blobs[i].getCentre();
		// Vector from observer to the centre
		Vector3 a = viewer - iCentre;
		// Initial brightness
		float brightness = 1;
		// For every blob that isn't i
		for (int j = 0; j < numBlobs; j++) {
			// If that blob is further from the viewer
			if (a.length() < (blobs[j].getCentre() - viewer).length()) {
				// Vector from the centre of blob j to the centre
				Vector3 b = blobs[j].getCentre() - iCentre;
				// Distance from the vector to the centre of the blob
				float d = (a.cross(b)).length() / a.length();
				float rad = blobs[j].getRadius();
				// If the distance is smaller than the radius of the blob
				if (d > rad) {
					// Subtract from the brightness according to intersection
						brightness -= gaussian(d, density, 2 * rad);
				}
			}
		}
		// Make sure the brightness value isn't negative
		if (brightness < 0) brightness = 0;
		// Horizontal vector
		Vector3 hor = Vector3(a.x, a.y, 0);
		// Angle between horizontal and a
		float alt = (hor.dot(a)) / (hor.length() * a.length());
		if (alt < 0) alt = -alt;
		// Find brightness travelling through the cloud
		Vector3 skylit = { brightness * alt, brightness * alt, brightness };

		float testBlueBrightness = 1 - brightness;
		float testRGBrightness = 1 - brightness * alt;

		// Set colour depending on whether the sky has added brightness
		if (blobs[i].getColour().x > skylit.x) skylit.x = blobs[i].getColour().x;
		if (blobs[i].getColour().y > skylit.y) skylit.y = blobs[i].getColour().y;
		if (blobs[i].getColour().z > skylit.z) skylit.z = blobs[i].getColour().z;
		blobs[i].setColour(skylit.x + ambient, skylit.y + ambient, skylit.z + ambient);

		/*blobs[i].setColour(blobs[i].getColour().x - testRGBrightness,
			blobs[i].getColour().y - testRGBrightness, 
			blobs[i].getColour().z - testBlueBrightness);*/
		

		/*float bVal = 0.72 * brightness;
		float rgVal = alt / (domeRadius * 5) * 0.3 * brightness;
		// Set the new colour
		blobs[i].setColour(rgVal + blobs[i].getColour().x,
			rgVal + blobs[i].getColour().y,
			brightness * blobs[i].getColour().z);*/
	}
}

float Builder::gaussian(float x, float height, float stdev) {
	const double EulerConstant = std::exp(1.0);
	return height*pow(EulerConstant, (-(x*x) / (2 * stdev*stdev)));
}

void Builder::shadeClouds() {
	lightMetas();
	if (skyLight) lightMetasSky();
	for (int i = 0; i < numBlobs; i++) {
		blobs[i].draw();
	}
}

void Builder::shadeCloudSimple() {
	lightMetaSimple();
	if (skyLight) lightMetasSkySimple();
	for (int i = 0; i < numBlobs; i++) {
		blobs[i].draw();
	}
}
