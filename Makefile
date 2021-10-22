INCLUDE := $(shell find src/ -type f -iname *.h -printf '-I%h\n' | sort -u)
./bin/main: src/main.cpp 				
	g++ -std=c++11 -Wall -Wno-unused-function -g -Iinclude/ $(INCLUDE) -o ./bin/main include/glad.c include/tiny_obj_loader.cpp src/*.cpp src/*/*.cpp ./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor

.PHONY: run						#"run" doesnt make files
clean:
	rm -f bin/main
run: ./bin/main						#when running "make run"
	./bin/main

