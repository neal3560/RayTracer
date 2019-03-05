#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Transform.h"

using namespace std;

class Shape {

public:
	Shape(int type, vec3 first, vec3 second, vec3 third);
	Shape(int type, vec3 center, float radius);
	~Shape();
	double intersect(vec3 eye, vec3 ray);

	int type;
	vec3 first;
	vec3 second;
	vec3 third;
	float radius;
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float emission[3];
	float shininess;
	mat4 transform;
};

#endif


