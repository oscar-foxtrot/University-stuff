CC = g++
CFLAGS = -c -Wall
OBJS = main.o includes/variable.o includes/function.o includes/anynum.o includes/vect.o

ifeq ($(OS), Windows_NT)
	OUT = program.exe
else
	OUT = program
endif

.DEFAULT_GOAL = all
.PHONY: clean


all: $(OUT)

$(OUT): main.o includes/variable.o includes/function.o includes/anynum.o
	$(CC) $(OBJS) -o $(OUT)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

includes/variable.o: includes/variable.cpp
	$(CC) $(CFLAGS) includes/variable.cpp -o includes/variable.o

includes/function.o: includes/function.cpp
	$(CC) $(CFLAGS) includes/function.cpp -o includes/function.o

includes/anynum.o: includes/anynum.cpp includes/vect.o
	$(CC) $(CFLAGS) includes/anynum.cpp -o includes/anynum.o

includes/vect.o: includes/vect.cpp
	$(CC) $(CFLAGS) includes/vect.cpp -o includes/vect.o

clean:
	rm $(OBJS)
