#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Transform.h" 
#include "RayTracer.h"

void matransform(stack<mat4> &transfstack, float * values);
void rightmultiply(const mat4 & M, stack<mat4> &transfstack);
bool readvals(stringstream &s, const int numvals, float * values);
void readfile(const char * filename, RayTracer * target);
