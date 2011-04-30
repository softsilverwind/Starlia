CXX=g++
CXXFLAGS=-Wall -O3

all: circle satellites satellites2 pong physics physics2 label label2

circle: circle.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLU -lstarlia -lGL

satellites: satellites.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLU -lstarlia -lGL

satellites2: satellites2.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLU -lstarlia -lGL

pong: pong.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLU -lstarlia -lGL

physics: physics.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLU -lstarlia -lGL

physics2: physics2.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLU -lstarlia -lGL

label: label.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLU -lstarlia -lGL

label2: label2.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLU -lstarlia -lGL

#1.exe: main1.cpp
#	i586-mingw32msvc-g++ $(CXXFLAGS) -o $@ $^ -I ~/Applications/freeglut/include/ -L ~/Applications/freeglut/lib/ -lopengl32 -lfreeglut -lglu32; strip 1.exe

clean:
	$(RM) *.o

distclean: clean
	$(RM) circle satellites satellites2 pong physics physics2 label label2
