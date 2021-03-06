#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\matrix\src\Matrices.h"
#include "Dependencies\matrix\src\Vectors.h"
#include "Header Files\Creator.h"
#include "Header Files\mainAssist.h"
#include "testing.h"

using namespace std;

bool validInput;

int main(int argc, char* argv[]) {
	//testing tests = testing(true, true, true);

	mainAssist assist = mainAssist("input.txt");
	int numBlobsMain = assist.getNumBlobs();
	float radMax = assist.getMaxRadius();

	cout << numBlobsMain << " blobs with a maximum radius of "
		<< radMax << " and a density of "
		<< assist.getDensity() << " at " << assist.getTime() << "." << endl;

	Vector3* centresMain = new Vector3[numBlobsMain];
	float* radius = new float[numBlobsMain];
	for (int i = 0; i < numBlobsMain; i++) {
		centresMain[i] = assist.randomCentre(1.5f, 1.5f, 0.3f, 0.6f);
		radius[i] = radMax + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / radMax));
	}

	glutInit(&argc, argv);
	Creator creator = Creator(centresMain, numBlobsMain, radius,
				assist.getTime(), assist.getDensity(), assist.getSkyLight());
	creator.work();
	return 0;
}