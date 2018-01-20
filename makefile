cc = g++
cFlags = -std=c++11 -pthread
cFiles = Wator.cpp
hFiles = Fish.h Shark.h

all: $(cFiles) $(hFiles) 
	$(cc) $(cFlags) Wator.cpp -o wator
