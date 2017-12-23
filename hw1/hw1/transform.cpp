// Transform.cpp: implementation of the Transform class.

#include <stdio.h>
#include "transform.h"

// up = y-axis, eye = z-axis. Using right-hand rule, the x-axis points left

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	const float radians = glm::radians(degrees);
	const vec3 unitAxis = glm::normalize(axis);
	printf("    Axis = (%.5f, %.5f, %.5f); Length = %.5f\n", axis.x, axis.y, axis.z, sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z));
	printf("    Unit = (%.5f, %.5f, %.5f); Length = %.5f\n", unitAxis.x, unitAxis.y, unitAxis.z, sqrt(unitAxis.x * unitAxis.x + unitAxis.y * unitAxis.y + unitAxis.z * unitAxis.z));
	
	//mat3 Ra;
	//Ra[0][0] = cos(radians) + (1 - cos(radians)) * unitAxis.x * unitAxis.x;
	//Ra[0][1] = (1 - cos(radians)) * unitAxis.x * unitAxis.y - sin(radians) * unitAxis.z;
	//Ra[0][2] = (1 - cos(radians)) * unitAxis.x * unitAxis.z + sin(radians) * unitAxis.y;
	//Ra[1][0] = (1 - cos(radians)) * unitAxis.x * unitAxis.y + sin(radians) * unitAxis.z;
	//Ra[1][1] = cos(radians) + (1 - cos(radians)) * unitAxis.y * unitAxis.y;
	//Ra[1][2] = (1 - cos(radians)) * unitAxis.y * unitAxis.z - sin(radians) * unitAxis.x;
	//Ra[2][0] = (1 - cos(radians)) * unitAxis.x * unitAxis.z - sin(radians) * unitAxis.y;
	//Ra[2][1] = (1 - cos(radians)) * unitAxis.y * unitAxis.z + sin(radians) * unitAxis.x;
	//Ra[2][2] = cos(radians) + (1 - cos(radians)) * unitAxis.z * unitAxis.z;
	//return Ra;

	mat3 I(1.0);
	mat3 aaT = mat3(unitAxis.x * unitAxis.x, unitAxis.x * unitAxis.y, unitAxis.x * unitAxis.z,
					unitAxis.x * unitAxis.y, unitAxis.y * unitAxis.y, unitAxis.y * unitAxis.z,
					unitAxis.x * unitAxis.z, unitAxis.y * unitAxis.z, unitAxis.z * unitAxis.z);
	mat3 aStar = mat3(0.0, unitAxis.z, -unitAxis.y,
					  -unitAxis.z, 0.0, unitAxis.x,
					  unitAxis.y, -unitAxis.x, 0.0);

	return mat3(cos(radians) * I + (float)(1.0 - cos(radians)) * aaT + sin(radians) * aStar);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// rotate about the up-axis
	eye = rotate(degrees, up) * eye;
	printf("Eye: x = %.5f, y = %.5f, z = %.5f; Distance: %.5f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// rotate about the right-axis
	eye = rotate(degrees, glm::cross(vec3(0.0, 0.0, 7.0), up)) * eye;
	printf("Eye: x = %.5f, y = %.5f, z = %.5f; Distance: %.5f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 RgluLookAt = mat4(u.x, v.x, w.x, 0,
						   u.y, v.y, w.y, 0,
						   u.z, v.z, w.z, 0,
						   -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1);
    return RgluLookAt;
}

Transform::Transform()
{}

Transform::~Transform()
{}
