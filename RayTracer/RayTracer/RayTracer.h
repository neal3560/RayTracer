#ifndef RAYTRACER
#define RAYTRACER
#define MAXOBJECTS 30
#include <vector>
#include "Transform.h"
class RayTracer{
	public:
		RayTracer();
		~RayTracer();
		int w, h;
		vec3 eye;
		vec3 up;
		vec3 center;
		float fovy;
		std::vector<vec3> vertexList;
		int numObject;

		struct object {
			int type;
			vec3 first;
			vec3 second;
			vec3 third;
			int radius;
			float ambient[4];
			float diffuse[4];
			float specular[4];
			float emission[4];
			float shininess;
			mat4 transform;
		} objects[MAXOBJECTS];
};


/*
EXTERN int amount; // The amount of rotation for each arrow press
EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye 
EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up 

#ifdef MAINPROGRAM 
vec3 eyeinit(0.0, 0.0, 5.0); // Initial eye position, also for resets
vec3 upinit(0.0, 1.0, 0.0); // Initial up position, also for resets
vec3 center(0.0, 0.0, 0.0); // Center look at point 
int amountinit = 5;
int w = 500, h = 500; // width and height 
float fovy = 90.0; // For field of view
#else 
EXTERN vec3 eyeinit;
EXTERN vec3 upinit;
EXTERN vec3 center;
EXTERN int amountinit;
EXTERN int w, h;
EXTERN float fovy;
#endif 

EXTERN bool useGlu; // Toggle use of "official" opengl/glm transform vs user 
EXTERN GLuint vertexshader, fragmentshader, shaderprogram; // shaders
EXTERN mat4 projection, modelview; // The mvp matrices
EXTERN GLuint projectionPos, modelviewPos; // Uniform locations of the above matrices
static enum { view, translate, scale } transop; // which operation to transform 
enum shape { cube, sphere, teapot };
EXTERN float sx, sy; // the scale in x and y 
EXTERN float tx, ty; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10;
EXTERN GLfloat lightposn[4 * numLights]; // Light Positions
EXTERN GLfloat lightcolor[4 * numLights]; // Light Colors
EXTERN GLfloat lightransf[4 * numLights]; // Lights transformed by modelview
EXTERN int numused;                     // How many lights are used 

// Materials (read from file) 
// With multiple objects, these are colors for each.
EXTERN GLfloat ambient[4];
EXTERN GLfloat diffuse[4];
EXTERN GLfloat specular[4];
EXTERN GLfloat emission[4];
EXTERN GLfloat shininess;

// For multiple objects, read from a file.  
const int maxobjects = 10;
EXTERN int numobjects;
EXTERN struct object {
	shape type;
	GLfloat size;
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat shininess;
	mat4 transform;
} objects[maxobjects];

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

