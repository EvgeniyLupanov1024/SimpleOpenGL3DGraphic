OUT_NAME = app-linux.out

all: ${OUT_NAME}
	./${OUT_NAME}

${OUT_NAME}: window.o
	g++ window.o -o ${OUT_NAME} -Wall -lGL -lglfw -lpthread

window.o: window.cpp
	g++ -c window.cpp
