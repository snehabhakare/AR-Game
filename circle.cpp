#include <cs775_ass1.hpp>
// #include <Box2D/Box2D.h>

//http://slabode.exofire.net/circle_draw.shtml
extern GLuint vao,vbo,shaderProgram;
extern b2World* world;
class circle{
	float cx,cy,r;
	b2Body* body;
	public:
	int num_vertices;
	glm::vec4* v_positions;
	glm::vec4* v_colors;
	
	circle(float cx_, float cy_, float r_, int num_vertices_) 
	{ 
		cx=cx_;
		cy=cy_;
		r=r_;
		num_vertices=num_vertices_;
		v_positions=(glm::vec4*) malloc (num_vertices*sizeof(glm::vec4));
		v_colors=(glm::vec4*) malloc (num_vertices*sizeof(glm::vec4));
		
		for(int ii = 0; ii < num_vertices; ii++) 
		{ 
			float theta = 2.0f * 3.1415926f * float(ii) / float(num_vertices);//get the current angle 

			float x = r * cosf(theta);//calculate the x component 
			float y = r * sinf(theta);//calculate the y component 

			v_positions[ii]=glm::vec4(x+cx,y+cy,0,1);
			v_colors[ii]=glm::vec4(1.0,0,0,1);
			
			// glVertex2f(x + cx, y + cy);//output vertex 

		} 

		b2BodyDef bodydef;
		bodydef.position.Set(cx,cy);
		bodydef.type=b2_dynamicBody;//change this TODO: 

		body=world->CreateBody(&bodydef);

		b2CircleShape shape;
		shape.m_p.Set(cx,cy);
		shape.m_radius=r;

		b2FixtureDef fixturedef;
		fixturedef.shape=&shape;
		fixturedef.density=1.0;
		body->CreateFixture(&fixturedef);
	}
	void printvertices(){
		for(int i=0;i<num_vertices;i++)
			std::cout<<v_positions[i].x<<" "<<v_positions[i].y<<" "<<v_positions[i].z<<std::endl;

	}

	void bind_pos(){
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);

		glGenVertexArrays (1, &vao);
		//Set it as the current array to be used by binding it
		glBindVertexArray (vao);

		//Ask GL for a Vertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);
		//Set it as the current buffer to be used by binding it
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		//Copy the points into the current buffer
		glBufferData (GL_ARRAY_BUFFER, (sizeof (v_positions) + sizeof(v_colors))*num_vertices*2, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, 2*sizeof(v_positions)*num_vertices, v_positions );
		glBufferSubData( GL_ARRAY_BUFFER, 2*sizeof(v_positions)*num_vertices, 2*sizeof(v_colors)*num_vertices, v_colors );
		GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		
		GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2*sizeof(v_positions)*num_vertices) );

		// uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

	}

	void update_buffer(){	
		// free (v_colors);
		// free (v_positions);
		// v_positions=(glm::vec4*) malloc (num_vertices*sizeof(glm::vec4));
		// v_colors=(glm::vec4*) malloc (num_vertices*sizeof(glm::vec4));
		b2Vec2 pos=body->GetPosition();
		std::cout<<pos.x<<" "<<pos.y<<" : "<<cx<<" "<<cy<<std::endl;
		if(pos.x==cx&&pos.y==cy)
			return;
		for(int ii = 0; ii < num_vertices; ii++) 
		{ 
			// float theta = 2.0f * 3.1415926f * float(ii) / float(num_vertices);//get the current angle 

			// float x = r * cosf(theta);//calculate the x component 
			// float y = r * sinf(theta);//calculate the y component 

			v_positions[ii]=v_positions[ii]+glm::vec4(pos.x-cx,pos.y-cy,0,0);
			// v_colors[ii]=glm::vec4(1.0,0,0,1);
			
			// glVertex2f(x + cx, y + cy);//output vertex 

		}	
		cx=pos.x;
		cy=pos.y;
		bind_pos();
	}
	void inc_cx(){
		cx+=0.1;
		update_buffer();
	}
	void dec_cx(){
		cx-=0.1;
		update_buffer();
	}
	void inc_cy(){
		cy+=0.1;
		update_buffer();
	}
	void dec_cy(){
		cy-=0.1;
		update_buffer();
	}


	~circle(){

		free (v_colors);
		free (v_positions);
	}


};


