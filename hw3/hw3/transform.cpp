// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
    const float radians = glm::radians(degrees);
    const vec3 unitAxis = glm::normalize(axis);

    // use Rodrigues' rotation formula
    mat3 I(1.0f);
    mat3 aaT = mat3(
        unitAxis.x * unitAxis.x, unitAxis.x * unitAxis.y, unitAxis.x * unitAxis.z,
        unitAxis.x * unitAxis.y, unitAxis.y * unitAxis.y, unitAxis.y * unitAxis.z,
        unitAxis.x * unitAxis.z, unitAxis.y * unitAxis.z, unitAxis.z * unitAxis.z);
    mat3 aStar = mat3(0.0f, unitAxis.z, -unitAxis.y,
                      -unitAxis.z, 0.0f, unitAxis.x,
                      unitAxis.y, -unitAxis.x, 0.0f);

    return mat3(cos(radians) * I + (1.0f - cos(radians)) * aaT
                + sin(radians) * aStar);
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
    // rotate the eye about the up-axis
    eye = rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
    // rotate both the eye and up-axis about their cross product
    eye = rotate(degrees, glm::cross(eye, up)) * eye;
    up = glm::normalize(rotate(degrees, glm::cross(eye, up)) * up);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
    vec3 w = glm::normalize(eye - center);
    vec3 u = glm::normalize(glm::cross(glm::normalize(up), w));
    vec3 v = glm::cross(w, u);

    return mat4(u.x, v.x, w.x, 0.0f,
                u.y, v.y, w.y, 0.0f,
                u.z, v.z, w.z, 0.0f,
                -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1.0f);
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar) {
    float d = 1 / glm::tan(glm::radians(fovy / 2.0f));
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -2.0f * zFar * zNear / (zFar - zNear);

    return mat4(d / aspect, 0.0f, 0.0f, 0.0f,
                0.0f, d, 0.0f, 0.0f,
                0.0f, 0.0f, A, -1.0f,
                0.0f, 0.0f, B, 0.0f);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
    return mat4(sx, 0.0f, 0.0f, 0.0f,
                0.0f, sy, 0.0f, 0.0f,
                0.0f, 0.0f, sz, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
    return mat4(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                tx, ty, tz, 1.0f);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) {
    vec3 x = glm::cross(up, zvec);
    vec3 y = glm::cross(zvec, x);
    return glm::normalize(y);
}


Transform::Transform() {

}

Transform::~Transform() {

}
