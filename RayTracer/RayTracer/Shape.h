#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Transform.h"
#include <cmath>

using namespace std;

class Shape {

public:
	Shape(int type, vec3 first, vec3 second, vec3 third);
	Shape(int type, vec3 center, float radius);
	~Shape();
	float intersect(vec3 eye, vec3 ray);
	void getInfo(float t, vec3 origin, vec3 ray, vec3 & posn, vec3 & normal);


	int type;
	vec3 first;
	vec3 second;
	vec3 third;
	float radius;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 emission;
	float shininess;
	mat4 transform;

	float min_x;
	float max_x;
	float min_y;
	float max_y;
	float min_z;
	float max_z;
};

#endif


