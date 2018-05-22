#To build executable for raspberry pi, run
#	make RPI=1

TARGET1 = bin/genspect
TARGET2 = bin/dtwmatch

CXX = g++
INC = -I./inc
LIB = `pkg-config --libs libavcodec libavformat libavutil libswresample`
DEBUG =

CFLAGS = -Wall -c --std=c++11
LFLAGS = -Wall -pthread

COMPILE = $(CXX) $(CFLAGS) $(INC) $(DEBUG) $^ -o $@
LINK = $(CXX) $(LFLAGS) $(LIB) $^ -o $@


.PHONY: all
all: $(TARGET1) $(TARGET2)#and other targets

$(TARGET1): build/genspect.o build/audiodec.o
	$(LINK)
$(TARGET2): build/dtwmatch.o build/audiodec.o
	$(LINK)

build/genspect.o: src/genspect.cpp
	$(COMPILE)
build/audiodec.o: src/audiodec.cpp
	$(COMPILE)
build/dtwmatch.o: src/dtwmatch.cpp
	$(COMPILE)

$(shell mkdir -p bin)
$(shell mkdir -p build)

clean:
	rm -frv *.o
	rm -frv ./build/*.o
