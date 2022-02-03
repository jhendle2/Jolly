# INLCLUDES=-I./include/ -I./include/data/ -I./include/data/primtypes/ -I./include/file/ -I./include/utils/ -I./include/interpreter/ -I./include/debug/
INLCLUDES=-I./include/ -I./include/file/ -I./include/parser/ -I./include/data/ -I./include/debug/
SRC=src/*/*.cpp
# src/*/*/*cpp

build:
	g++ -g $(INLCLUDES) -Wall -o jolly jolly.cpp $(SRC)
	echo -ne '\007'

test:
	make build
	./jolly --debug ./examples/test2.jolly

t:
	g++ -g -Wall -o test test.cpp
	./t