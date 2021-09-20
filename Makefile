./bin/main: src/main.cpp
	g++ -std=c++11 -o ./bin/main src/main.cpp
.PHONY: run
run: ./bin/main
	./bin/main

