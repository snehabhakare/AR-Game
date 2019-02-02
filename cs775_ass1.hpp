/*
  A program which opens a window and draws the "color cube."

  Use the arrow keys and PgUp,PgDn, 
  keys to make the cube move.

  Written by - 
               Parag Chaudhuri
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <Box2D/Box2D.h>
#include "circle.cpp"
#include "rectangle.cpp"
// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=5.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling = true;
//Running variable to toggle wireframe/solid modelling
bool solid = true;
GLuint vbo, vao;
GLuint shaderProgram;

int l_comm = 0;
int r_comm = 0;
int u_comm = 0;
int d_comm = 0;

b2World* world = new b2World(b2Vec2(0,-10));
circle c(2.5,7.5,0.5,200);
rectangle* r;
std::vector<rectangle*> maze;

//-------------------------------------------------------------------------

#endif
