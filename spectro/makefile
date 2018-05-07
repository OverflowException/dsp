#To build executable for raspberry pi, run
#	make RPI=1

TARGET = bin/spect

CXX = g++
INC = -I./inc
LIB = `pkg-config --libs libavcodec libavformat libavutil libswresample`
DEBUG =

CFLAGS = -Wall -c --std=c++11
LFLAGS = -Wall -pthread

COMPILE = $(CXX) $(CFLAGS) $(INC) $(DEBUG) $^ -o $@
LINK = $(CXX) $(LFLAGS) $(LIB) $^ -o $@


.PHONY: all
all: $(TARGET) #and other targets

$(TARGET): build/main.o build/audiodec.o
	$(LINK)
build/main.o: src/main.cpp
	$(COMPILE)
build/audiodec.o: src/audiodec.cpp
	$(COMPILE)

$(shell mkdir -p bin)
$(shell mkdir -p build)

clean:
	rm -frv *.o
	rm -frv ./build/*.o
