#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <FreeImage.h>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#include "RayTracer.h"
#define INFINITY 10000

int main(int argc, char* argv[]) {
	RayTracer * target = new RayTracer(argv[1]);
	//cout << "read complete\n";
	int pix = target->w * target->h;
	BYTE *pixels = new BYTE[3 * pix];
	
	for (int i = 0; i < target->h; i++) {
		for (int j = 0; j < target->w; j++) {
			//cout << "in forloop\n";
			vec3 eye_ray = target->getRay(i, j);
			vec3 normal, posn;
			Shape * hit = target->intersect(target->eye, eye_ray, posn, normal);
			if (hit) {
				//cout << "in hit\n";
				vec3 color = target->getColor(eye_ray, posn, normal, hit, 5);
				int start = (i * target->w + j) * 3;
				pixels[start] = (int)(color[2] * 255);
				pixels[start + 1] = (int)(color[1] * 255);
				pixels[start + 2] =(int)(color[0] * 255);
 			}
		}
		cout << "complete " << (float)i / target->h << "\n";
	}
	
	FreeImage_Initialise();
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, target->w, target->h, target->w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	FreeImage_Save(FIF_PNG, img, argv[2], 0);
	
	FreeImage_DeInitialise();

	delete pixels;
	delete target;
}