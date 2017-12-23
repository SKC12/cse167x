// transform.cpp: implementation of the Transform class.

#include "transform.h"

// helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
    const float radians = glm::radians(degrees);
    const vec3 unitAxis = glm::normalize(axis);

    // use Rodrigues' rotation formula
    mat3 I(1.0);
    mat3 aaT = mat3(
        unitAxis.x * unitAxis.x, unitAxis.x * unitAxis.y, unitAxis.x * unitAxis.z,
        unitAxis.x * unitAxis.y, unitAxis.y * unitAxis.y, unitAxis.y * unitAxis.z,
        unitAxis.x * unitAxis.z, unitAxis.y * unitAxis.z, unitAxis.z * unitAxis.z);
    mat3 aStar = mat3(0, unitAxis.z, -unitAxis.y,
                      -unitAxis.z, 0, unitAxis.x,
                      unitAxis.y, -unitAxis.x, 0);

    return mat3(cos(radians) * I + (float)(1.0 - cos(radians)) * aaT
                + sin(radians) * aStar);
}

// transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
    // rotate the eye about the up-axis
    eye = rotate(degrees, up) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
    // rotate both the eye and up-axis about their cross product
    eye = rotate(degrees, glm::cross(eye, up)) * eye;
    up = rotate(degrees, glm::cross(eye, up)) * up;
}

// derivation of gluLookAt
mat4 Transform::lookAt(vec3 eye, vec3 up) {
    // create a coordinate frame for the camera
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, w));
    vec3 v = glm::cross(w, u);

    // translate first, then rotate
    mat4 MgluLookAt = mat4(
        u.x, v.x, w.x, 0,
        u.y, v.y, w.y, 0,
        u.z, v.z, w.z, 0,
        -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1);

    return MgluLookAt;
}
