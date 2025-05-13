CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: movie1 movie2

movie1: movie1.cpp
	$(CXX) $(CXXFLAGS) movie1.cpp -o movie1

movie2: movie2.cpp
	$(CXX) $(CXXFLAGS) movie2.cpp -o movie2

clean:
	rm -f movie1 movie2 movie1.exe movie2.exe
