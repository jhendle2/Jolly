INLCLUDE=./include/
SRC=./src/*.cpp

build:
	g++ -g -I$(INLCLUDE) -Wall -o jolly jolly.cpp src/*.cpp

test:
	make build
	./jolly test2.jolly