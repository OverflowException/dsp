#To build executable for raspberry pi, run
#	make RPI=1

TARGET = bin/decoder

CXX = gcc
INC = -I./inc
LIB = -lavcodec -lavformat -lavutil -lswresample
DEBUG =

CFLAGS = -Wall -c
LFLAGS = -Wall -pthread

COMPILE = $(CXX) $(CFLAGS) $(INC) $(DEBUG) $^ -o $@
LINK = $(CXX) $(LFLAGS) $(LIB) $^ -o $@


.PHONY: all
all: $(TARGET) #and other targets

$(TARGET): build/main.o build/audiodec.o
	$(LINK)
build/main.o: src/main.c
	$(COMPILE)
build/audiodec.o: src/audiodec.c
	$(COMPILE)

$(shell mkdir -p bin)
$(shell mkdir -p build)

clean:
	rm -frv *.o
	rm -frv ./build/*.o
