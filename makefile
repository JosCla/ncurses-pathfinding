CXX = g++
CXXFLAGS = -g -Wall
LIBS = -lncurses

CPPFILES = src/main.cpp src/perlin.cpp src/dijkstra.cpp
OBJFILES = $(CPPFILES:.cpp=.o)

TARGET = maze

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJFILES)
	$(RM) $(TARGET)
