#pragma once
#include "Dependencies\matrix\src\Vectors.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

class mainAssist
{
public:
	mainAssist(string address);
	Vector3 randomCentre(float xRange, float yRange, float zRange, float maxRad);
	int getNumBlobs();
	float getMaxRadius();
	float getDensity();
	float getTime();
	bool getSkyLight();
	~mainAssist();
private:
	float parseToInt(string s);
	float timeToFloat(string s);
	ifstream readInput();
	void readVals();
	string address;
	bool isValidInput;
	int numBlobsA;
	float maxRadiusA;
	float densityA;
	float timeA;
	bool skyLightA;
};

