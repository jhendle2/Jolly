INLCLUDES=-I./v2/include/ -I./v2/include/parser/ -I./v2/include/types/
SRC=v2/src/*.cpp v2/src/*/*.cpp

build:
	g++ -g $(INLCLUDES) -Wall -o jolly jolly.cpp $(SRC)

test:
	make build
	./jolly test2.jolly