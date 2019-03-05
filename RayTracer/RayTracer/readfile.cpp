#include "RayTracer.h"

void RayTracer::matransform(stack<mat4> &transfstack, float* values)
{
	mat4 transform = transfstack.top();
	vec4 valvec = vec4(values[0], values[1], values[2], values[3]);
	vec4 newval = transform * valvec;
	for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void RayTracer::rightmultiply(const mat4 & M, stack<mat4> &transfstack)
{
	mat4 &T = transfstack.top();
	T = T * M;
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool RayTracer::readvals(stringstream &s, const int numvals, float* values)
{
	for (int i = 0; i < numvals; i++) {
		s >> values[i];
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}

void RayTracer::readfile(const char* filename)
{
	string str, cmd;
	ifstream in;
	in.open(filename);
	if (in.is_open()) {

		// I need to implement a matrix stack to store transforms.  
		// This is done using standard STL Templates 
		stack <mat4> transfstack;
		transfstack.push(mat4(1.0));  // identity

		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				// Ruled out comment and blank lines 

				stringstream s(str);
				s >> cmd;
				int i;
				float values[10]; // Position and color for light, colors for others
									// Up to 10 params for cameras.  
				bool validinput; // Validity of input 

				// Process the light, add it to database.
				// Lighting Command
				/*if (cmd == "light") {
					if (numused == numLights) { // No more Lights 
						cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
					}
					else {
						validinput = readvals(s, 8, values); // Position/color for lts.
						if (validinput) {
							lightposn[numused * 4] = values[0];
							lightposn[numused * 4 + 1] = values[1];
							lightposn[numused * 4 + 2] = values[2];
							lightposn[numused * 4 + 3] = values[3];
							lightcolor[numused * 4] = values[4];
							lightcolor[numused * 4 + 1] = values[5];
							lightcolor[numused * 4 + 2] = values[6];
							lightcolor[numused * 4 + 3] = values[7];
							++numused;
						}
					}
				}*/

				// Material Commands 
				// Ambient, diffuse, specular, shininess properties for each object.
				// Filling this in is pretty straightforward, so I've left it in 
				// the skeleton, also as a hint of how to do the more complex ones.
				// Note that no transforms/stacks are applied to the colors. 

				if (cmd == "ambient") {
					validinput = readvals(s, 3, values); // colors 
					if (validinput) {
						for (i = 0; i < 3; i++) {
							ambient[i] = values[i];
						}
					}
				}
				else if (cmd == "diffuse") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						for (i = 0; i < 3; i++) {
							diffuse[i] = values[i];
						}
					}
				}
				else if (cmd == "specular") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						for (i = 0; i <3; i++) {
							specular[i] = values[i];
						}
					}
				}
				else if (cmd == "emission") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						for (i = 0; i < 3; i++) {
							emission[i] = values[i];
						}
					}
				}
				else if (cmd == "shininess") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						shininess = values[0];
					}
				}
				else if (cmd == "size") {
					validinput = readvals(s, 2, values);
					if (validinput) {
						w = (int)values[0]; 
						h = (int)values[1];
					}
				}
				else if (cmd == "camera") {
					validinput = readvals(s, 10, values); // 10 values eye cen up fov
					if (validinput) {
						eye = vec3(values[0], values[1], values[2]);
						center = vec3(values[3], values[4], values[5]);
						up = normalize(vec3(values[6], values[7], values[8]));
						fovy = values[9];
					}
				}
				else if (cmd == "vertex") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						vertexList->push_back(vec3(values[0], values[1], values[2]));
					}
				}
				else if (cmd == "sphere") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						
						// Set the object's transform
						Shape * sphere = new Shape(0, vec3(values[0], values[1], values[2]), values[3]);
						sphere->transform = transfstack.top();

						// Set the object's light properties
						for (i = 0; i < 4; i++) {
							(sphere->ambient)[i] = ambient[i];
							(sphere->diffuse)[i] = diffuse[i];
							(sphere->specular)[i] = specular[i];
							(sphere->emission)[i] = emission[i];
						}
						sphere->shininess = shininess;

						objects->push_back(sphere);
						
					}
				}
				else if (cmd == "tri") {
					validinput = readvals(s, 3, values);
					if (validinput) {
					
						// Set the object's transform
						Shape * tri = new Shape(1,
							vertexList->at((int)values[0]),
							vertexList->at((int)values[1]),
							vertexList->at((int)values[2])
						);

						tri->transform = transfstack.top();

						// Set the object's light properties
						for (i = 0; i < 4; i++) {
							(tri->ambient)[i] = ambient[i];
							(tri->diffuse)[i] = diffuse[i];
							(tri->specular)[i] = specular[i];
							(tri->emission)[i] = emission[i];
						}
						tri->shininess = shininess;

						objects->push_back(tri);
					}
				}
				else if (cmd == "translate") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						mat4 T = Transform::translate(values[0], values[1], values[2]);
						rightmultiply(T, transfstack);
					}
				}
				else if (cmd == "scale") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						mat4 T = Transform::scale(values[0], values[1], values[2]);
						rightmultiply(T, transfstack);
					}
				}
				else if (cmd == "rotate") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						mat3 r = Transform::rotate(values[3], vec3(values[0], values[1], values[2]));
						mat4 T = mat4(r);
						rightmultiply(T, transfstack);
					}
				}

				// I include the basic push/pop code for matrix stacks
				else if (cmd == "pushTransform") {
					transfstack.push(transfstack.top());
				}
				else if (cmd == "popTransform") {
					if (transfstack.size() <= 1) {
						cerr << "Stack has no elements.  Cannot Pop\n";
					}
					else {
						transfstack.pop();
					}
				}

				else {
					cerr << "Unknown Command: " << cmd << " Skipping \n";
				}
			}
			getline(in, str);
		}
	}
	else {
		cerr << "Unable to Open Input Data File " << filename << "\n";
		throw 2;
	}
}
