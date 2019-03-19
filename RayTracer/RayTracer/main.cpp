#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <FreeImage.h>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

using namespace std;

#include "RayTracer.h"
#define INFINITY 10000

int main(int argc, char* argv[]) {
	cout << "running " << argv[1] << endl;
	auto start = chrono::high_resolution_clock::now();
	RayTracer * target = new RayTracer(argv[1]);
	int pix = target->w * target->h; 
	BYTE *pixels = new BYTE[3 * pix];
	
#pragma omp parallel for
	for (int i = 0; i < target->h; i++) {
		for (int j = 0; j < target->w; j++) {
			vec3 eye_ray = target->getRay(i, j);
			vec3 normal, posn;
			Shape * hit = target->intersect(target->eye, eye_ray, posn, normal);
			if (hit) {
				vec3 color = target->getColor(eye_ray, posn, normal, hit, 5);
				int start = (i * target->w + j) * 3;
				pixels[start] = (int)(color[2] * 255);
				pixels[start + 1] = (int)(color[1] * 255);
				pixels[start + 2] =(int)(color[0] * 255);
 			}
		}
		//cout << float(i) / target->h << "\n";
		//cout << "computing...\n";
	}
	
	FreeImage_Initialise();
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, target->w, target->h, target->w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	FreeImage_Save(FIF_PNG, img, argv[2], 0);
	
	FreeImage_DeInitialise();
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
	cout << "Complete in " << duration.count() << " s."<< endl;
	char c;
	cout << "Press any key to exit.\n";
	cin >> c;
	delete pixels;
	delete target;
}