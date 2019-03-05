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

	int pix = target->w * target->h;
	BYTE *pixels = new BYTE[3 * pix];
	
	for (int i = 0; i < target->h; i++) {
		for (int j = 0; j < target->w; j++) {
			vec3 ray = target->getRay(i, j);
			double min_t = INFINITY;
			Shape * min_primitive = NULL;
			for (vector<Shape*>::iterator p = target->objects->begin(); p != target->objects->end(); p++) {
				double t = (*p)->intersect(target->eye, ray);
				if (t > 0 && t < min_t) {
					min_primitive = *p;
					min_t = t;
				}
			}
			if (min_primitive) {
				int start = (i * target->w + j) * 3;
				pixels[start] = (int)(min_primitive->ambient[2] * 255);
				pixels[start + 1] = (int)(min_primitive->ambient[1] * 255);
				pixels[start + 2] =(int)(min_primitive->ambient[0] * 255);
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