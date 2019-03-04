#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <FreeImage.h>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


#define MAINPROGRAM
using namespace std;

#include "RayTracer.h"
#include "Transform.h"
#include "readfile.h"

int main(int argc, char* argv[]) {
	RayTracer * target = new RayTracer();
	readfile("scene1.test", target);
	int pix = target->w * target->h;
	BYTE *pixels = new BYTE[3 * pix];

	for (int i = 0; i < 3 * pix; i++) {
		pixels[i] = 0x00;
	}

	FreeImage_Initialise();
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, target->w, target->h, target->w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(FIF_PNG, img, "test.png", 0);
	FreeImage_DeInitialise();

	int i;
	cin >> i;

	delete pixels;
}