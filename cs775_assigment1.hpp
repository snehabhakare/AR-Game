#pragma once
#ifdef _WIN32
#  include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __APPLE__
#  include <GL/gl.h>
#  include <GL/glut.h>
#else
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#endif
#include <AR/ar.h>
#include <AR/gsub.h>
#include <AR/video.h>
#include <Box2D/Box2D.h>
#include <vector>
#include <ctime>
#include "rectangle.cpp"
#include "circle.cpp"
#include "maze.cpp"

#define             CPARA_NAME       "camera_para.dat"
#define             VPARA_NAME       "Data/cameraSetting-%08x%08x.dat"
#define             PATT_NAME        "hiro.patt"

ARHandle           *arHandle;
ARPattHandle       *arPattHandle;
AR3DHandle         *ar3DHandle;
ARGViewportHandle  *vp;
int                 xsize, ysize;
int                 flipMode = 0;
int                 patt_id;
double              patt_width = 80.0;
int                 count = 0;
char                fps[256];
char                errValue[256];
int                 distF = 0;
int                 contF = 0;
ARParamLT          *gCparamLT = NULL;

static void   init(int argc, char *argv[]);
static void   keyFunc( unsigned char key, int x, int y );
static void   cleanup(void);
static void   mainLoop(void);
static void   draw( ARdouble trans[3][4] );

float gravity_constant=0.5;
float frame_rate=1/10.0;
float coeff_of_rest=0.6f;
b2World* world=new b2World(b2Vec2(5,5));

const float height_of_each_elem=10;
float B=80,L=100,W=1;
circle ball(2,10,10);
std::vector<rectangle*> maze_list;

int players;
double elapsed_secs = 0;
clock_t begin, end;
std::vector<double> scores;
