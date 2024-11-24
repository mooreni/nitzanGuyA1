# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: clean link

link: compile
	@echo "Linking object files."
	g++ -o bin/simulation bin/main.o

compile: src/main.cpp
	@echo "Compiling binary files."
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

clean:
	@echo "Cleaning bin directory."
	rm -f bin/*
