CXX=g++
CXXFLAGS=-Wall -O3 -g -std=c++0x
AR=ar
ARFLAGS=-cvsr

all: libstarlia.a

libstarlia.a: basicRender.o core.o math.o object.o model.o label.o layer.o texture.o timer.o sound.o starLight.o camera.o
	$(AR) $(ARFLAGS) $@ $^

model.o: model.h
object.o: object.h
basicRender.o: basicRender.h
core.o: core.h
math.o: math.h
label.o: label.h
layer.o: layer.h
texture.o: texture.h
timer.o: timer.h
sound.o: sound.h
starLight.o: starLight.h

clean:
	$(RM) *.o

distclean: clean
	$(RM) libstarlia.a

install: all
	su -c "cp libstarlia.a /usr/local/lib && cp basicRender.h core.h math.h structs.h starlia.h object.h model.h label.h layer.h texture.h timer.h sound.h starLight.h camera.h /usr/local/include"

uninstall:
	su -c "$(RM) /usr/local/lib/libstarlia.a && rm /usr/local/include/basicRender.h /usr/local/include/core.h /usr/local/include/math.h /usr/local/include/starlia.h /usr/local/include/structs.h /usr/local/include/object.h /usr/local/include/model.h /usr/local/include/label.h /usr/local/include/layer.h /usr/local/include/timer.h /usr/local/include/sound.h /usr/local/include/starLight.h /usr/local/include/camera.h /usr/local/include/texture.h"
