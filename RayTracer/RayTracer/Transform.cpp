// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	float x = axis[0];
	float y = axis[1];
	float z = axis[2];
	float theta = degrees * pi / 180;
	mat3 I(1, 0, 0, 0, 1, 0, 0, 0, 1);
	mat3 para(x*x, x*y, x*z, x*y, y*y, y*z, z*x, z*y, z*z);
	mat3 perp(0, z, y*(-1), (-1)*z, 0, x, y, (-1)*x, 0);
	mat3 rotate = cosf(theta) * I + (1 - cosf(theta)) * para + sinf(theta) * perp;
	return rotate;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
	mat3 rotate = Transform::rotate(degrees, normalize(up));
	eye = rotate * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
	vec3 horizontal = normalize(cross(eye, up));
	mat3 rotate = Transform::rotate(degrees, horizontal);
	eye = rotate * eye;
	up = rotate * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	vec3 a = eye - center;
	vec3 w = normalize(a);
	vec3 u = normalize(cross(up, a));
	vec3 v = cross(w, u);
	mat3 R = transpose(mat3(u, v, w));
	mat4 R2 = mat4(R);
	mat4 T = mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, eye[0] * (-1), eye[1] * (-1), eye[2] * (-1), 1);
	return R2 * T;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float rf = fovy / 180 * pi;
	float d = 1 / tanf(rf / 2);
	float A = (zNear + zFar) / (zNear - zFar);
	float B = 2 * zNear * zFar / (zNear - zFar);
	mat4 ret = mat4(d / aspect, 0.0, 0.0, 0.0, 0.0, d, 0.0, 0.0, 0.0, 0.0, A, -1.0, 0.0, 0.0, B, 0.0);
	return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 ret(sx, 0.0, 0.0, 0.0, 0.0, sy, 0.0, 0.0, 0.0, 0.0, sz, 0.0, 0.0, 0.0, 0.0, 1);
	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 ret(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, tx, ty, tz, 1);
	return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
