#include "Header Files\mainAssist.h"
#include "Dependencies\matrix\src\Vectors.h"
#include "Header Files\BlobS.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Poor man's approximation of PI
#define PI 3.1415926535898
// Degrees to radians
#define DTOR (PI / 180.0f)

using namespace std;

mainAssist::mainAssist(string address) {
	this->address = address;
	readVals();
}

float mainAssist::parseToInt(string s) {
	s = s.substr(s.find("=") + 1, s.length());
	return atof(s.c_str());
}

float mainAssist::timeToFloat(string s) {
	s = s.substr(s.find("=") + 1, s.length());
	if (s.length() == 0) s = "12";
	return atof(s.c_str());
}

ifstream mainAssist::readInput() {
	ifstream input;
	input.open(address);
	if (input.fail()) {
		cout << "Input read failed" << endl;
	}
	return input;
}

void mainAssist::readVals() {
	ifstream input = readInput();
	string numblobsIn;
	string radMaxIn;
	string densityIn;
	string timeIn;
	string skyLightIn;
	input >> numblobsIn >> radMaxIn >> densityIn >> timeIn >> skyLightIn;
	int skyLightInput = parseToInt(skyLightIn.substr(skyLightIn.find("=") + 1, skyLightIn.length()));
	if (skyLightInput == 1) {
		this->skyLightA = true;
	}
	else {
		this->skyLightA = false;
	}
	numBlobsA = parseToInt(numblobsIn);
	if (numBlobsA < 0) numBlobsA = 0;
	maxRadiusA = parseToInt(radMaxIn);
	if (maxRadiusA < 0) maxRadiusA = 0;
	densityA = parseToInt(densityIn);
	if (densityA < 0) densityA = 0;
	timeA = timeToFloat(timeIn);
	if (timeA < 0) timeA = 0;
	if (timeA >= 24 ) timeA = 0;
}

int mainAssist::getNumBlobs() {
	return this->numBlobsA;
}
float mainAssist::getMaxRadius() {
	return this->maxRadiusA;
}
float mainAssist::getDensity() {
	return this->densityA;
}
float mainAssist::getTime() {
	return this->timeA;
}
bool mainAssist::getSkyLight() {
	return this->skyLightA;
}

Vector3 mainAssist::randomCentre(float xRange, float yRange, float zRange, float maxRad) {
	Vector3 point = Vector3(10, 10, 10);
	while (point.length() > maxRad) {
		point = Vector3{ -xRange / 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (xRange / 2 - -xRange / 2))),
			-yRange / 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (yRange / 2 - -yRange / 2))),
			static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / zRange)) };
	}

	return point;
}

mainAssist::~mainAssist()
{
}
