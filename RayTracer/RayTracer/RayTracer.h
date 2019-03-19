#ifndef RAYTRACER_H
#define RAYTRACER_H
#include <algorithm>
#include <tuple>
#include <unordered_map> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Transform.h"
#include "Shape.h"

class RayTracer{
	public:
		RayTracer(char* filename);
		~RayTracer();

		void matransform(stack<mat4> &transfstack, float * values);
		void rightmultiply(const mat4 & M, stack<mat4> &transfstack);
		bool readvals(stringstream &s, const int numvals, float * values);
		void readfile(const char * filename);
		vec3 getRay(int i, int j);
		Shape * intersect(vec3 origin, vec3 ray, vec3 &posn, vec3 &normal);
		vec3 getColor(vec3 ray, vec3 posn, vec3 normal, Shape * Obj, int depth);
		vec3 ComputeLight(const vec3 direction, const vec3 lightcolor, const vec3 normal,
			const vec3 halfvec, const vec3 mydiffuse, const vec3 myspecular,
			const float myshininess);

		int w, h;
		vec3 eye;
		vec3 up;
		vec3 center;
		float fovy;

		vec3 attenuation;
		vector<vec3> *lightcolor;
		vector<vec4> *lightposn;

		float ambient[3];
		float diffuse[3];
		float specular[3];
		float emission[3];
		float shininess;

		vector<vec3> * vertexList;
		vector<Shape*> * objects;
		mat4 modelview;

		int maxdepth;

		float min_x;
		float max_x;
		float min_y;
		float max_y;
		float min_z;
		float max_z;

		typedef std::tuple<int, int, int> grid;
		struct key_hash : public unary_function<grid, size_t> 
		{
			std::size_t operator() (const grid &k) const
			{
				return hash<float>()(get<0>(k)) ^ hash<float>()(get<1>(k)) ^ hash<float>()(get<2>(k));
			}
		};
		unordered_map<tuple<int, int, int>, vector<Shape*>, key_hash> grids;
};

#endif

