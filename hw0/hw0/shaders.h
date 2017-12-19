/**
 * @file     shaders.h
 * @author   Phi Luu
 * @date     December 18, 2017
 *
 * @brief    UC San DiegoX: CSE167x Computer Graphics
 *
 * @section  DESCRIPTION
 *
 * This is a simple demo program written for CSE167 by Ravi Ramamoorthi
 * This program corresponds to the final OpenGL lecture on shading.
 * Modified September 2016 by Hoang Tran to exclusively use modern OpenGL
 *
 * This program draws some simple geometry, a plane with four pillars
 * textures the ground plane, and adds in a teapot that moves
 * Lighting effects are also included with fragment shaders
 * The keyboard function should be clear about the keystrokes
 * The mouse can be used to zoom into and out of the scene
 */

#include <iostream>
#include <string>

#ifndef __INCLUDESHADERS
# define __INCLUDESHADERS

std::string textFileRead(const char* filename);
void programerrors(const GLint program);
void shadererrors(const GLint shader);
GLuint initshaders(GLenum type, const char* filename);
GLuint initprogram(GLuint vertexshader, GLuint fragmentshader);

#endif // ifndef __INCLUDESHADERS
