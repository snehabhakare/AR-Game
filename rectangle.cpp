#pragma once
#include "cs775_assigment1.hpp"
extern const float height_of_each_elem;
extern b2World* world;
extern float W;
static void
mydrawBox(GLfloat size1,GLfloat size2,GLfloat size3, GLenum type)
{
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size1 / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size1 / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size2 / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size2 / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size3 / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size3 / 2;

  for (i = 5; i >= 0; i--) {
    glBegin(type);
    glNormal3fv(&n[i][0]);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3fv(&v[faces[i][0]][0]);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3fv(&v[faces[i][1]][0]);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3fv(&v[faces[i][2]][0]);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void
myglutSolidCuboid(GLdouble size1,GLdouble size2,GLdouble size3)
{
  mydrawBox(size1,size2,size3 ,GL_QUADS);
}
class rectangle{
    float half_l,half_b;
    float cx,cy;
    bool go_to_box2d;
    float z_translate;
    b2Body* body;
    
    public:

    rectangle(float half_l_,float half_b_,float cx_,float cy_,bool go_to_box2d_=true,float z_translate_=1.5*height_of_each_elem){
        cx = cx_;
		cy = cy_;
		half_l = half_l_;
        half_b = half_b_;
        z_translate=z_translate_;
        go_to_box2d = go_to_box2d_;

        b2BodyDef bodydef;
		bodydef.position = b2Vec2(cx,cy);
		bodydef.type = b2_staticBody;//change this TODO: 

		body = world->CreateBody(&bodydef);

		b2PolygonShape shape;
		shape.SetAsBox(half_l/2,half_b/2);

		b2FixtureDef fixturedef;
		fixturedef.shape = &shape;
		fixturedef.density = 1.0;
    fixturedef.friction=0.0f;
    fixturedef.restitution=0.5f;
		body->CreateFixture(&fixturedef);
	
    }


    void draw(){
        if(!go_to_box2d){
          glColor3f(1.0f,0.0f,0.0f);
        }
        glTranslatef(cx,cy,z_translate);
        myglutSolidCuboid(half_l+W,half_b+W,height_of_each_elem);
        glTranslatef(-cx,-cy,-z_translate);
        
    }

    ~rectangle(){

    }
};

