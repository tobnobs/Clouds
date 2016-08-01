#include "Header Files\BlobS.h"
#include "Header Files\Builder.h"
#include "Header Files\Creator.h"
#include "Header Files\mainAssist.h"
#include "testing.h"

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\matrix\src\Matrices.h"
#include "Dependencies\matrix\src\Vectors.h"

using namespace std;

BlobS blob1;
BlobS blob2;
BlobS blob3;

void windowMainTest();

testing::testing(bool testBlobS, bool testBuilder, bool testMainAssist) {
	this->pass = true;

	blob1 = BlobS(Vector3{ 0.0, -1.0, 0.0 }, 0.8, Vector3{ 0.0, 0.0, -1.0 });
	blob1.genBillboard();
	blob2 = BlobS(Vector3{ 0.0, 0.0, 0.0 }, 0.6, Vector3{ 0.0, 0.0, -1.0 });
	blob2.genBillboard();
	blob3 = BlobS(Vector3{ 0.0, 1.0, 0.0 }, 0.4, Vector3{ 0.0, 0.0, -1.0 });
	blob3.genBillboard();

	if (testBlobS) blobSTest();
	if (testBuilder) builderTest();
	if (testMainAssist) mainAssistTest();
}

void testing::blobSTest() {
	Vector3 testCentre = blob1.getCentre();
	pass = testCentre.x == 0.0 && testCentre.y == -1.0 && testCentre.z == 0.0;
	cout << "1.1.1 : BlobS: getCentre() = " << pass << endl;
	testCentre = blob2.getCentre();
	pass = testCentre.x == 0.0 && testCentre.y == 0.0 && testCentre.z == 0.0;
	cout << "1.1.2 : BlobS: getCentre() = " << pass << endl;
	testCentre = blob3.getCentre();
	pass = testCentre.x == 0.0 && testCentre.y == 1.0 && testCentre.z == 0.0;
	cout << "1.1.3 : BlobS: getCentre() = " << pass << endl;

	float testRadius = blob1.getRadius();
	pass = testRadius == 0.8f;
	cout << "1.2.1 : BlobS: getRadius() = " << pass << endl;
	testRadius = blob2.getRadius();
	pass = testRadius == 0.6f;
	cout << "1.2.2 : BlobS: getRadius() = " << pass << endl;
	testRadius = blob3.getRadius();
	pass = testRadius == 0.4f;
	cout << "1.2.3 : BlobS: getRadius() = " << pass << endl;

	Vector3 testColour = blob1.getColour();
	pass = testColour.x == 1.0 && testColour.y == 1.0 && testColour.z == 1.0;
	cout << "1.3.1 : BlobS: getColour() = " << pass << endl;
	testColour = blob2.getColour();
	pass = testColour.x == 1.0 && testColour.y == 1.0 && testColour.z == 1.0;
	cout << "1.3.2 : BlobS: getColour() = " << pass << endl;
	testColour = blob3.getColour();
	pass = testColour.x == 1.0 && testColour.y == 1.0 && testColour.z == 1.0;
	cout << "1.3.3 : BlobS: getColour() = " << pass << endl;

	blob1.setColour(0.1, 0.2, 0.3);
	testColour = blob1.getColour();
	pass = testColour - Vector3(0.1, 0.2, 0.3) == Vector3(0.0, 0.0, 0.0);
	cout << "1.4.1 : BlobS: setColour() = " << pass << endl;
	blob1.setColour(0.5, 0.5, 0.5);
	testColour = blob1.getColour();
	pass = testColour - Vector3(0.5, 0.5, 0.5) == Vector3(0.0, 0.0, 0.0);
	cout << "1.4.2 : BlobS: setColour() = " << pass << endl;
	blob2.setColour(0.7, 0.7, 0.7);
	testColour = blob2.getColour();
	pass = testColour - Vector3(0.7, 0.7, 0.7) == Vector3(0.0, 0.0, 0.0);
	cout << "1.4.3 : BlobS: setColour() = " << pass << endl;
}

void testing::builderTest() {
	Vector3 centres1[] = { { 0.0, -1.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } };
	float radii1[] = { 0.8, 0.6, 0.4 };

	Builder builder1 = Builder(centres1, 3, radii1, 12, { 0.0, 0.0, -1.0 }, 0.01, false);
	Vector3 TestLightColour = builder1.getLightColour();
	pass = TestLightColour.x == 1.0 && TestLightColour.y == 1.0 && TestLightColour.z == 1.0;
	cout << "2.1.1 : Builder: calcLightColour() = " << pass << endl;

	builder1 = Builder(centres1, 3, radii1, 6.1, { 0.0, 0.0, -1.0 }, 0.01, false);
	Vector3 TestLightColour2 = builder1.getLightColour();
	pass = TestLightColour2.x < TestLightColour.x
		|| TestLightColour2.y < TestLightColour.y
		|| TestLightColour2.z < TestLightColour.z;
	cout << "2.1.2 : Builder: calcLightColour() = " << pass << endl;

	builder1 = Builder(centres1, 3, radii1, 21.1, { 0.0, 0.0, -1.0 }, 0.01, false);
	TestLightColour2 = builder1.getLightColour();
	pass = TestLightColour2.x < TestLightColour.x
		|| TestLightColour2.y < TestLightColour.y
		|| TestLightColour2.z < TestLightColour.z;
	cout << "2.1.3 : Builder: calcLightColour() = " << pass << endl;

	builder1 = Builder(centres1, 3, radii1, 1.1, { 0.0, 0.0, -1.0 }, 0.01, false);
	TestLightColour2 = builder1.getLightColour();
	pass = TestLightColour2.x == 0.0 && TestLightColour2.y == 0.0 && TestLightColour2.z == 0.0;
	cout << "2.1.4 : Builder: calcLightColour() = " << pass << endl;

	float TestGaussian = builder1.gaussian(0.0, 1.0, 0.5);
	pass = TestGaussian == 1;
	cout << "2.2.1 : Builder: gaussian() = " << pass << endl;
	TestGaussian = builder1.gaussian(0.2, 1.0, 0.5);
	pass = TestGaussian < 1;
	cout << "2.2.2 : Builder: gaussian() = " << pass << " : " << TestGaussian << endl;
	float TestGaussian2 = builder1.gaussian(0.4, 1.0, 0.5);
	pass = TestGaussian2 < TestGaussian;
	cout << "2.2.3 : Builder: gaussian() = " << pass << " : " << TestGaussian2 << endl;
	TestGaussian2 = builder1.gaussian(0.2, 0.7, 0.5);
	pass = TestGaussian2 < TestGaussian;
	cout << "2.2.4 : Builder: gaussian() = " << pass << " : " << TestGaussian2 << endl;
	float TestGaussian3 = builder1.gaussian(0.4, 0.7, 0.5);
	pass = TestGaussian3 < TestGaussian2;
	cout << "2.2.5 : Builder: gaussian() = " << pass << " : " << TestGaussian3 << endl;
	TestGaussian2 = builder1.gaussian(0.2, 1.0, 0.3);
	pass = TestGaussian2 < TestGaussian;
	cout << "2.2.6 : Builder: gaussian() = " << pass << " : " << TestGaussian2 << endl;
}

void testing::mainAssistTest() {
	mainAssist assist1 = mainAssist("TestInput.txt");
	pass = assist1.getNumBlobs() == 0;
	cout << "3.1.1 : mainAssist: readVals() = " << pass << endl;
	pass = assist1.getMaxRadius() == 0;
	cout << "3.1.2 : mainAssist: readVals() = " << pass << endl;
	pass = assist1.getDensity() == 0;
	cout << "3.1.3 : mainAssist: readVals() = " << pass << endl;
	pass = assist1.getTime() == 12;
	cout << "3.1.4 : mainAssist: readVals() = " << pass << endl;
	pass = !assist1.getSkyLight();
	cout << "3.1.5 : mainAssist: readVals() = " << pass << endl;

	Vector3 centreTest1 = assist1.randomCentre(1.0, 1.0, 1.0, 5.0);
	Vector3 centreTest2 = assist1.randomCentre(1.0, 1.0, 1.0, 5.0);
	pass = !(centreTest1 - centreTest2 == Vector3(0.0, 0.0, 0.0));
	centreTest2 = assist1.randomCentre(1.0, 1.0, 1.0, 5.0);
	pass = pass || !(centreTest1 - centreTest2 == Vector3(0.0, 0.0, 0.0));
	centreTest2 = assist1.randomCentre(1.0, 1.0, 1.0, 5.0);
	pass = pass || !(centreTest1 - centreTest2 == Vector3(0.0, 0.0, 0.0));
	cout << "mainAssist: randomCentre() = " << pass << endl;
}

testing::~testing() {}