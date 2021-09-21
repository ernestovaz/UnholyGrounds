# Default case, when running only "make"
./bin/main: src/main.cpp 				#depends on src/main.cpp
	g++ -std=c++11 -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o ./bin/main src/main.cpp
.PHONY: run						#"run" doesnt make files
run: ./bin/main						#when running "make run"
	./bin/main

