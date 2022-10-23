CC  = g++
OPT = -O3
LIBS = -lntl -lgmp -lm -lrt
FLAGS = -c -fPIC --std=c++11 -Wall -Winvalid-pch -Wnon-virtual-dtor
LINK_FLAGS = -Wl,--no-undefined -Wl,--as-needed -Wl,-O1 -shared -fPIC -Wl,--start-group -Wl,-soname,libgro18.so -lntl -lgmp -Wl,--end-group

all: libgro18.so

install: libgro18.so
	cp libgro18.so /usr/local/lib/libgro18.so

uninstall:
	rm -rf /usr/local/lib/libgro18.so

libgro18.so: libgro18.o
	$(CC) -o libgro18.so libgro18.o $(LINK_FLAGS)

libgro18.o: libgro18.cpp libgro18.h
	$(CC) $(OPT) $(FLAGS) libgro18.cpp $(LIBS)

clean: 
	rm -f *.o *.so


