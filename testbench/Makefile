CXX=g++
CXXFLAGS=-Wall -O3 -g

all: circle satellites satellites2 pong physics physics2 label label2 label3 model satellitesModel coord

circle: circle.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

satellites: satellites.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

satellites2: satellites2.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

pong: pong.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

physics: physics.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

physics2: physics2.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

label: label.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

label2: label2.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

label3: label3.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

model: model.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

satellitesModel: satellitesModel.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

coord: coord.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lSDL -lGLU -lstarlia -lGL -lSDL_mixer

#1.exe: main1.cpp
#	i586-mingw32msvc-g++ $(CXXFLAGS) -o $@ $^ -I ~/Applications/freeglut/include/ -L ~/Applications/freeglut/lib/ -lopengl32 -lfreeglut -lglu32; strip 1.exe

clean:
	$(RM) *.o

distclean: clean
	$(RM) circle satellites satellites2 pong physics physics2 label label2 label3 model satellitesModel coord
