# Default case, when running only "make"
./bin/main: src/main.cpp 				#depends on src/main.cpp
	g++ -std=c++11 -Wall -Wno-unused-function -g -Iinclude/ -Isrc/ -Isrc/renderer -Isrc/input -Isrc/commands -o ./bin/main include/glad.c include/tiny_obj_loader.cpp src/*.cpp src/*/*.cpp ./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor

.PHONY: run						#"run" doesnt make files
run: ./bin/main						#when running "make run"
	./bin/main

