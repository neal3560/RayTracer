#include "Shape.h"
#include <cmath>
#include <algorithm>
#include <iostream>
Shape::Shape(int type, vec3 first, vec3 second, vec3 third) {
	this->type = type;
	this->first = first;
	this->second = second;
	this->third = third;
}

Shape::Shape(int type, vec3 center, float radius){
	this->type = type;
	this->first = center;
	this->radius = radius;
}

Shape::~Shape(){

}

float Shape::intersect(vec3 eye, vec3 ray){
	vec3 eye_in = vec3(inverse(transform) * vec4(eye, 1));
	vec3 ray_in = vec3(inverse(transform) * vec4(ray, 0));
	if (type == 0) {
		float a = dot(ray_in, ray_in);
		float b = 2 * dot(ray_in, eye_in - first);
		float c = dot(eye_in - first, eye_in - first) - radius * radius;
		float delta = b * b - 4 * a * c;
		if (delta > 0) {
			float r1 = (-b + sqrt(delta)) / (2 * a);
			float r2 = (-b - sqrt(delta)) / (2 * a);
			if(r1 > 0 && r2 > 0)
				return min(r1, r2);
			else if (r1 > 0 && r2 < 0) {
				return r1;
			}
			else if (r1 < 0 && r2 > 0) {
				return r2;
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	else if (type == 1) {
		vec3 normal = normalize(cross(third - first, second - first));
		float t = (dot(first, normal) - dot(eye_in, normal)) / dot(ray_in, normal);
		vec3 P = eye_in + t * ray_in;
		
		vec3 v0 = second - first;
		vec3 v1 = third - first;
		vec3 v2 = P - first;
	
		float d00 = dot(v0, v0);
		float d01 = dot(v0, v1);
		float d11 = dot(v1, v1);
		float d20 = dot(v2, v0);
		float d21 = dot(v2, v1);

		float denom = d00 * d11 - d01 * d01;

		float alpha = (d11 * d20 - d01 * d21) / denom;
		float beta = (d00 * d21 - d01 * d20) / denom;
		float gamma = 1.0f - alpha - beta;
		
		//cout << alpha + beta + gamma << "\n";
		if (alpha >= 0 && beta >= 0 && gamma >= 0) {
			return t;
		}
		else {
			return -1;
		}
 	}
}

void Shape::getInfo(float t, vec3 origin, vec3 ray, vec3 & posn, vec3 & normal) {
	vec3 eye_in = vec3(inverse(transform) * vec4(origin, 1));
	vec3 ray_in = vec3(inverse(transform) * vec4(ray, 0));

	vec4 hit = vec4(eye_in + t * ray_in, 1);
	posn = vec3(transform * hit);

	vec3 norm;
	if (type == 0) {
		norm = normalize(vec3(hit) - first);
	}
	else {
		norm = normalize(cross(third - first, second - first));
		if (dot(ray_in, norm) > 0) {
			norm = -1.0f * norm;
		}
	}
	normal = normalize(mat3(transpose(inverse(transform))) * norm);
}