#pragma once
#include "cs775_assigment1.hpp"

extern const float height_of_each_elem;
extern b2World* world;
extern float coeff_of_rest;

class circle{
    float r;
    float cx,cy;
    float z_translate;
    int slice=400,stack=400;
    
    public:
    b2Body* body;

    circle(float r_,float cx_,float cy_){
        cx = cx_;
		cy = cy_;
        r=r_;
    
        b2BodyDef bodydef;
		bodydef.position = b2Vec2(cx,cy);
		bodydef.type = b2_dynamicBody;

		body = world->CreateBody(&bodydef);

		b2CircleShape shape;
		shape.m_p = b2Vec2(0,0);
		shape.m_radius = r;

		b2FixtureDef fixturedef;
		fixturedef.shape = &shape;
		fixturedef.density = 1.0;
        fixturedef.friction=0.0f;
        fixturedef.restitution=coeff_of_rest;

		body->CreateFixture(&fixturedef);
    }

    void draw(){
        glTranslatef(cx,cy,r+height_of_each_elem);
        glutSolidSphere(r,slice,stack);
        glTranslatef(-cx,-cy,-(r+height_of_each_elem));
    }

    void update(){
        b2Vec2 pos= body->GetPosition();
        cx=pos.x;
        cy=pos.y;
    }

    void display(){
        printf("%f,%f\n",cx,cy);
    }

    ~circle(){
    }
};

