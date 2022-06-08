OUT_NAME = app-linux.out

all: ${OUT_NAME}
	./${OUT_NAME}

${OUT_NAME}: window.cpp
	g++ window.cpp -o ${OUT_NAME} -Wall -lGL -lpthread
