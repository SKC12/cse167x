// Transform.cpp: implementation of the Transform class.

#include <stdio.h>
#include "transform.h"

// up = y-axis, eye = z-axis. Using right-hand rule, the x-axis points left

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	mat3 Ra;
	float radians = degrees * pi / 180.0;

	Ra[0][0] = cos(radians) + (1 - cos(radians)) * pow(axis.x, 2);
	Ra[0][1] = (1 - cos(radians)) * axis.x * axis.y - sin(radians) * axis.z;
	Ra[0][2] = (1 - cos(radians)) * axis.x * axis.z + sin(radians) * axis.y;
	Ra[1][0] = (1 - cos(radians)) * axis.x * axis.y + sin(radians) * axis.z;
	Ra[1][1] = cos(radians) + (1 - cos(radians)) * pow(axis.y, 2);
	Ra[1][2] = (1 - cos(radians)) * axis.y * axis.z - sin(radians) * axis.x;
	Ra[2][0] = (1 - cos(radians)) * axis.x * axis.z - sin(radians) * axis.y;
	Ra[2][1] = (1 - cos(radians)) * axis.y * axis.z + sin(radians) * axis.x;
	Ra[2][2] = cos(radians) + (1 - cos(radians)) * pow(axis.z, 2);

    return Ra;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// rotate clockwise about the up-axis => negative angle
	eye = rotate(-degrees, up) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// rotate counter-clockwise about the left-axis
	// left-axis = unit of upinit x eyeinit = unit of (7, 0, 0) = (1, 0, 0)
	eye = rotate(degrees, vec3(1.0, 0, 0)) * eye;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// TODO
	mat4 RgluLookAt = mat4(1.0, up.x, eye.x, 0,
						   0, up.y, eye.y, 0,
						   0, up.z, eye.z, 0,
						   -eye.x, -glm::dot(up, eye), -glm::dot(eye, eye), 1);
    return RgluLookAt;
}

Transform::Transform()
{}

Transform::~Transform()
{}
