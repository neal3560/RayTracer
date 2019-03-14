# include "RayTracer.h"
# include <algorithm>
RayTracer::RayTracer(char* filename)
{
	vertexList = new vector<vec3>();
	objects = new vector<Shape*>();
	lightcolor = new vector<vec3>();
	lightposn = new vector<vec4>();
	attenuation = vec3(1, 0, 0);
	//output = new char();
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

Shape * RayTracer::intersect(vec3 origin, vec3 ray, vec3 & posn, vec3 & normal) {
	float min_t = INFINITY;
	Shape * min_primitive = NULL;
	for (vector<Shape*>::iterator p = objects->begin(); p != objects->end(); p++) {
		float t = (*p)->intersect(origin, ray);
		if (t > 0 && t < min_t) {
			min_primitive = *p;
			min_t = t;
		}
	}
	if (min_primitive) {
		min_primitive->getInfo(min_t, origin, ray, posn, normal);
	}
	return min_primitive;
}

vec3 RayTracer::getColor(vec3 ray, vec3 posn, vec3 normal, Shape * Obj, int depth) {
	vec3 hitposn;
	vec3 hitnormal;
	vec3 color = Obj->ambient + Obj->emission;
	for (int i = 0; i < lightposn->size(); i++) {
		vec3 eye_dirt = -1.0f * ray;
		vec3 light_posn = vec3(lightposn->at(i));
		vec3 light_color = vec3(lightcolor->at(i));
		vec3 light_ray;
		if (lightposn->at(i)[3] == 0) {
			light_ray = normalize(light_posn);
			Shape * hit = intersect(posn + 0.01f * light_ray, light_ray, hitposn, hitnormal);
			if (hit) {
				break;
			}
			else {
				vec3 H = normalize(eye_dirt + light_ray);
				vec3 col = ComputeLight(light_ray, light_color, normal, H, Obj->diffuse, Obj->specular, Obj->shininess);
				color = color + col;
			}
		}
		else {
			light_ray = normalize(light_posn - posn);
			Shape * hit = intersect(posn + 0.01f * light_ray, light_ray, hitposn, hitnormal);
			if (hit) {
				if (length(light_posn - posn) > length(hitposn - posn))
					break;
			}
			else {
				vec3 H = normalize(eye_dirt + light_ray);
				vec3 col = ComputeLight(light_ray, light_color, normal, H, Obj->diffuse, Obj->specular, Obj->shininess);
				float dist = length(light_posn - posn);
				color = color + col / (attenuation[0] + attenuation[1] * dist + attenuation[2] * dist * dist);
			}
		}
	}
	if (depth != 1) {
		vec3 reflect = normalize(ray - 2 * dot(ray, normal) * normal);
		vec3 next_normal, next_posn;
		Shape * hit = intersect(posn + 0.01f * reflect, reflect, next_posn, next_normal);
		if (hit) {
			color = color + Obj->specular * getColor(reflect, next_posn, next_normal, hit, depth - 1);
		}
	}
	if (color[0] > 1){
		color[0] = 1;
	}
	if (color[1] > 1) {
		color[1] = 1;
	}
	if (color[2] > 1) {
		color[2] = 1;
	}
	return color;
}

vec3 RayTracer::ComputeLight(const vec3 direction, const vec3 lightcolor, const vec3 normal,
	const vec3 halfvec, const vec3 mydiffuse, const vec3 myspecular,
	const float myshininess) {
	float nDotL = dot(normal, direction);
	//cout << nDotL << "\n";
	vec3 lambert = mydiffuse * lightcolor * max(nDotL, 0.0f);

	float nDotH = dot(normal, halfvec);
	vec3 phong = myspecular * lightcolor * pow(max(nDotH, 0.0f), myshininess);

	vec3 retval = lambert + phong;
	return retval;
}