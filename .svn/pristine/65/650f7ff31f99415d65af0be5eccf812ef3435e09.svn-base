#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\matrix\src\Matrices.h"
#include "Dependencies\matrix\src\Vectors.h"

class Builder {
public:
	Builder(Vector3 centres[], int numBlobs, float radius[], float time, Vector3 observer, float density, bool skyLight);
	void drawDome();
	void drawCloud();
	void lightMetas();
	void lightMetasSky();
	void lightMetaSimple();
	void lightMetasSkySimple();
	Vector3 getLightColour();
	float gaussian(float x, float height, float stdev);
private:
	void generateDome();
	void generateCloud();
	void shadeClouds();
	void shadeCloudSimple();
	Vector3 calcLightColour(float time);
	bool domeGen, cloudGen, skyLight;
	int numBlobs;
	float density;
	float ambient;
	Vector3* centres;
	Vector3 lightSource;
	Vector3 lightColour;
	float blueVal;
	Vector3 viewer;
};