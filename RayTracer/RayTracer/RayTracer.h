#ifndef RAYTRACER_H
#define RAYTRACER_H
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

		int w, h;
		vec3 eye;
		vec3 up;
		vec3 center;
		float fovy;

		float ambient[3];
		float diffuse[3];
		float specular[3];
		float emission[3];
		float shininess;

		vector<vec3> * vertexList;
		vector<Shape*> * objects;
		mat4 modelview;

};





/*
// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10;
EXTERN GLfloat lightposn[4 * numLights]; // Light Positions
EXTERN GLfloat lightcolor[4 * numLights]; // Light Colors
EXTERN GLfloat lightransf[4 * numLights]; // Lights transformed by modelview
EXTERN int numused;                     // How many lights are used 




// Variables to set uniform params for lighting fragment shader 
EXTERN GLuint lightcol;
EXTERN GLuint lightpos;
EXTERN GLuint numusedcol;
EXTERN GLuint enablelighting;
EXTERN GLuint ambientcol;
EXTERN GLuint diffusecol;
EXTERN GLuint specularcol;
EXTERN GLuint emissioncol;
EXTERN GLuint shininesscol;*/

#endif

