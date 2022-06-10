OUT_NAME = app-linux.out

all: ${OUT_NAME}
	./${OUT_NAME}

${OUT_NAME}: window.o shader.o
	g++ window.o shader.o -o ${OUT_NAME} -Wall -lGLEW -lGL -lglfw -lpthread

window.o: window.cpp
	g++ -c window.cpp

shader.o: shader.cpp shader.h
	g++ -c shader.cpp
