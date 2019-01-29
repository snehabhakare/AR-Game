CC=g++ 

OPENGLLIB= -lGL -std=gnu++0x
GLEWLIB= -lGLEW 
GLFWLIB = -lglfw
BOX2DLIB= -lBox2D
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(BOX2DLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=cs775_ass1
SRCS=cs775_ass1.cpp gl_framework.cpp shader_util.cpp 
INCLUDES=gl_framework.hpp shader_util.hpp cs775_ass1.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
