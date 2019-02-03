INC_DIR= usr/local/include
LIB_DIR= /usr/lib
BIN_DIR= .

CC=g++ -std=gnu++0x
LDFLAG=-L/usr/lib/x86_64-linux-gnu -L/usr/lib64 -L$(LIB_DIR)/linux-x86_64 -L$(LIB_DIR)
LIBS= -lARgsub -lARvideo -lAR -lARICP -lAR -lglut -lGLU -lGL -lX11 -lm -lpthread -ljpeg -lBox2D
CFLAG= -O3 -fPIC -march=core2 -DHAVE_NFT=1 -I/usr/include/x86_64-linux-gnu -I$(INC_DIR)

OBJS =
HEADDERS =

all: $(BIN_DIR)/cs775_assignment1

$(BIN_DIR)/cs775_assignment1: cs775_assignment1.o $(OBJS)
	${CC} -o $(BIN_DIR)/cs775_assignment1 cs775_assignment1.o $(OBJS) $(LDFLAG) $(LIBS)

cs775_assignment1.o: cs775_assignment1.cpp $(HEADDERS)
	${CC} -c $(CFLAG) cs775_assignment1.cpp

clean:
	rm -f *.o
	rm -f $(BIN_DIR)/cs775_assignment1

allclean:
	rm -f *.o
	rm -f $(BIN_DIR)/cs775_assignment1
	rm -f Makefile

distclean:
	rm -f *.o
	rm -f Makefile
