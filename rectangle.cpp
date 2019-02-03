#pragma once
#include "cs775_assigment1.hpp"

extern const float height_of_each_elem;
extern b2World* world;
extern float W;
extern float coeff_of_rest;

static void mydrawBox(GLfloat size1,GLfloat size2,GLfloat size3, GLenum type,int go_to_box2d)
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

    const GLubyte cube_faces [6][4] = { /* ccw-winding */
    /* +z */ {3, 2, 1, 0}, /* -y */ {2, 3, 7, 6}, /* +y */ {0, 1, 5, 4},
    /* -x */ {3, 0, 4, 7}, /* +x */ {1, 2, 6, 5}, /* -z */ {4, 5, 6, 7} };
    
    // const GLubyte cube_vertex_colors [8][4] = {
    // {255, 255, 255, 255}, {255, 255, 0, 255}, {0, 255, 0, 255}, {0, 255, 255, 255},
    // {255, 0, 255, 255}, {255, 0, 0, 255}, {0, 0, 0, 255}, {0, 0, 255, 255} };
    const GLubyte cube_vertex_colors [8][4] = {
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
    
    GLint i;
    GLfloat v[8][3];
    
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size1 / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size1 / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size2 / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size2 / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size3 / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size3 / 2;
    if(go_to_box2d==1){
        const GLubyte cube_vertex_colors [8][4] = {
            {192, 192,192, 0}, 
            {192, 192,192, 0}, 
            {192, 192,192, 0}, 
            {192, 192,192, 0},
            {192, 192,192, 0}, 
            {192, 192,192, 0}, 
            {192, 192,192, 0}, 
            {192, 192,192, 0} 
        };
        
        glPushMatrix(); // Save world coordinate system.
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, cube_vertex_colors);
        glVertexPointer(3, GL_FLOAT, 0, v);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        for (i = 0; i < 6; i++) {
            glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, &(cube_faces[i][0]));
        }
        glDisableClientState(GL_COLOR_ARRAY);
        glColor4ub(0, 0, 0, 255);
        for (i = 0; i < 6; i++) {
            glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, &(cube_faces[i][0]));
        }
        glPopMatrix();    // Restore world coordinate system.
    }
    else if(go_to_box2d==2){//end
        const GLubyte cube_vertex_colors [8][4] = {
            {255, 51,51, 255}, 
            {255, 51,51, 255}, 
            {255, 51,51, 255}, 
            {255, 51,51, 255},
            {255, 51,51, 255}, 
            {255, 51,51, 255}, 
            {255, 51,51, 255}, 
            {255, 51,51, 255} 
        };
        
        glPushMatrix(); // Save world coordinate system.
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, cube_vertex_colors);
        glVertexPointer(3, GL_FLOAT, 0, v);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        for (i = 0; i < 6; i++) {
            glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, &(cube_faces[i][0]));
        }
        glDisableClientState(GL_COLOR_ARRAY);
        glColor4ub(0, 0, 0, 255);
        for (i = 0; i < 6; i++) {
            glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, &(cube_faces[i][0]));
        }
        glPopMatrix();    // Restore world coordinate system.
    }
    else if(go_to_box2d==3){//start
        const GLubyte cube_vertex_colors [8][4] = {
            {128, 255,0, 255}, 
            {128, 255,0, 255}, 
            {128, 255,0, 255}, 
            {128, 255,0, 255},
            {128, 255,0, 255}, 
            {128, 255,0, 255}, 
            {128, 255,0, 255}, 
            {128, 255,0, 255} 
        };
        
        glPushMatrix(); // Save world coordinate system.
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, cube_vertex_colors);
        glVertexPointer(3, GL_FLOAT, 0, v);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        for (i = 0; i < 6; i++) {
            glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, &(cube_faces[i][0]));
        }
        glDisableClientState(GL_COLOR_ARRAY);
        glColor4ub(0, 0, 0, 255);
        for (i = 0; i < 6; i++) {
            glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, &(cube_faces[i][0]));
        }
        glPopMatrix();    // Restore world coordinate system.
    }
    else{
        glPushMatrix(); // Save world coordinate system.
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, cube_vertex_colors);
        glVertexPointer(3, GL_FLOAT, 0, v);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        for (i = 0; i < 6; i++) {
            glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, &(cube_faces[i][0]));
        }
        glDisableClientState(GL_COLOR_ARRAY);
        glColor4ub(0, 0, 0, 255);
        for (i = 0; i < 6; i++) {
            glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, &(cube_faces[i][0]));
        }
        glPopMatrix();    // Restore world coordinate system.
    }
}

void myglutSolidCuboid(GLdouble size1,GLdouble size2,GLdouble size3,int go_to_box2d)
{
    mydrawBox(size1,size2,size3 ,GL_QUADS,go_to_box2d);
}

class rectangle{
    float half_l,half_b;
    float cx,cy;
    int go_to_box2d;
    float z_translate;
    b2Body* body;

    public:

    rectangle(float half_l_,float half_b_,float cx_,float cy_,int go_to_box2d_=0,float z_translate_=1.5*height_of_each_elem){
        cx = cx_;
        cy = cy_;
        half_l = half_l_;
        half_b = half_b_;
        z_translate=z_translate_;
        go_to_box2d = go_to_box2d_;
        if(go_to_box2d==0){
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
            fixturedef.restitution=coeff_of_rest;
            body->CreateFixture(&fixturedef);
        }
    }

    void draw(){
        glTranslatef(cx,cy,z_translate);
        myglutSolidCuboid(half_l+W,half_b+W,height_of_each_elem,go_to_box2d);
        glTranslatef(-cx,-cy,-z_translate);
    }

    ~rectangle(){
    }
};

