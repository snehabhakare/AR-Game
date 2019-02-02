#include <cs775_ass1.hpp>

extern GLuint vao,vbo,shaderProgram;
extern b2World* world;

class rectangle{
    float half_l,half_b;
	float cx,cy;
	b2Body* body;
    public:
	int num_vertices;
	glm::vec4* v_positions;
	glm::vec4* v_colors;
	
	rectangle(float cx_, float cy_, float half_l_,float half_b_) 
	{ 
		cx = cx_;
		cy = cy_;
		half_l = half_l_;
        half_b = half_b_;

		num_vertices = 4;
		v_positions = (glm::vec4*) malloc (num_vertices*sizeof(glm::vec4));
		v_colors = (glm::vec4*) malloc (num_vertices*sizeof(glm::vec4));
        
        v_positions[0] = glm::vec4(cx+half_l,cy+half_b,0,1);
        v_positions[1] = glm::vec4(cx-half_l,cy+half_b,0,1);
        v_positions[2] = glm::vec4(cx-half_l,cy-half_b,0,1);
        v_positions[3] = glm::vec4(cx+half_l,cy-half_b,0,1);

        v_colors[0] = glm::vec4(0.0,1.0,0,1);
		v_colors[1] = glm::vec4(0.0,1.0,0,1);
		v_colors[2] = glm::vec4(0.0,1.0,0,1);
		v_colors[3] = glm::vec4(0.0,1.0,0,1);
		
		b2BodyDef bodydef;
		bodydef.position = b2Vec2(cx,cy);
		bodydef.type = b2_staticBody;//change this TODO: 

		body = world->CreateBody(&bodydef);

		b2PolygonShape shape;
		shape.SetAsBox(half_l,half_b);

		b2FixtureDef fixturedef;
		fixturedef.shape = &shape;
		fixturedef.density = 1.0;
		body->CreateFixture(&fixturedef);
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

	~rectangle(){

		free (v_colors);
		free (v_positions);
	}
};