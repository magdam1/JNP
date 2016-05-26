CC=g++
CFLAGS = -Wall -Wextra -O0 -g -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -std=c++11 -DDEBUG -Wfatal-errors
DEP=function_maxima.h
ALL=main

all: $(ALL)

$(ALL) : % : %.cc $(DEP)
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(ALL)

.PHONY: all clean