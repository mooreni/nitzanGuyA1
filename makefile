# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: clean link

link: compile
	@echo "Linking object files."
	g++ -o bin/simulation bin/main.o bin/Settlement.o bin/SelectionPolicy.o bin/Facility.o

compile: src/main.cpp
	@echo "Compiling binary files."
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Facility.o src/Facility.cpp


clean:
	@echo "Cleaning bin directory."
	rm -f bin/*
