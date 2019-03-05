# include "RayTracer.h"
RayTracer::RayTracer(char* filename)
{
	vertexList = new vector<vec3>();
	objects = new vector<Shape*>();
	readfile(filename);
}

RayTracer::~RayTracer()
{
	delete vertexList;
	for (vector<Shape*>::iterator p = objects->begin(); p != objects->end(); p++) {
		delete *p;
	}
	delete objects;
}

vec3 RayTracer::getRay(int i, int j) {
	float x = i + 0.5;
	float y = j + 0.5;
	vec3 a = eye - center;
	vec3 ww = normalize(a);
	vec3 u = normalize(cross(up, a));
	vec3 v = cross(ww, u);
	float beta = tan(fovy * pi / 360) * (h / 2 - x) / (h/2);
	float alpha = tan(fovy * pi / 360) * w / h * (y - w/2) / (w/2);
	return normalize(vec3(alpha * u + beta * v - ww));
}