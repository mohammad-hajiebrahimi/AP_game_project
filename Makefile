CC_EXEC= g++
CC_FLAGS= -c

CC= ${CC_EXEC} ${CC_FLAGS}
BUILD_DIR= build
SRC_DIR= src

${BUILD_DIR}/a.out: ${BUILD_DIR}/main.o
	g++ ${BUILD_DIR}/main.o -o ${BUILD_DIR}/a.out -lsfml-graphics -lsfml-window -lsfml-system

${BUILD_DIR}/main.o: main.cpp ${SRC_DIR}/magic.hh ${SRC_DIR}/readmap.hh ${SRC_DIR}/mapgraphic.hh ${SRC_DIR}/textgraphic.hh ${SRC_DIR}/agentgraphic.hh
	g++ -c main.cpp -o ${BUILD_DIR}/main.o

clean:
	rm ${BUILD_DIR}/*.o ${BUILD_DIR}/a.out

run:
	${BUILD_DIR}/./a.out
