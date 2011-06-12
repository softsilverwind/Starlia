CXX=g++
CXXFLAGS=-Wall -O3 -g
AR=ar
ARFLAGS=-cvsr

all: libstarlia.a

libstarlia.a: basicRender.o core.o starMath.o object.o model.o label.o layer.o texture.o
	$(AR) $(ARFLAGS) $@ $^

model.o: model.h
object.o: object.h
basicRender.o: basicRender.h
core.o: core.h
starMath.o: starMath.h
label.o: label.h
layer.o: layer.h
texture.o: texture.h

clean:
	$(RM) *.o

distclean: clean
	$(RM) libstarlia.a

install: all
	su -c "cp libstarlia.a /usr/local/lib && cp basicRender.h core.h starMath.h structs.h starlia.h object.h model.h label.h layer.h /usr/local/include"

uninstall:
	su -c "$(RM) /usr/local/lib/libstarlia.a && rm /usr/local/include/basicRender.h /usr/local/include/core.h /usr/local/include/starMath.h /usr/local/include/starlia.h /usr/local/include/structs.h /usr/local/include/object.h /usr/local/include/model.h /usr/local/include/label.h /usr/local/include/layer.h"
