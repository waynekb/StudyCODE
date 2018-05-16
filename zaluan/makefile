OBJS= testc.o foo.o

all: test

test: $(OBJS)
	$(CXX) $(OBJS) -o testc	

testc.o :testc.c
	$(CC) -c testc.c -o testc.o 
foo.o: foo.cc foo.h
	$(CXX) -c foo.cc -o foo.o

.PHONY: clean
clean:
	rm foo.o;
	rm testc;