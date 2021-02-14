CXX = g++
CXXFLAGS = -g -Wall
LIBS = -lncurses

SRC = src/
CPPFILES = $(wildcard $(SRC)*.cpp) $(wildcard $(SRC)**/*.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)

TARGET = ncpath

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJFILES)
	$(RM) $(TARGET)
