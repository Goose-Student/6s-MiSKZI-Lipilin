CXX = g++
CXXFLAGS = -Wall -std=c++11
SOURCES = $(wildcard *.cpp)
EXECS = $(SOURCES:.cpp=.exe)

all: $(EXECS)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(EXECS)
