CXX = g++
CXXFLAGS = -g -Wall
LIBS = -lncurses

CPPFILES = src/main.cpp src/perlin.cpp src/dijkstra.cpp src/direction.cpp
OBJFILES = $(CPPFILES:.cpp=.o)

TARGET = maze

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJFILES)
	$(RM) $(TARGET)
