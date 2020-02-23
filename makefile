OBJECTS = main.o upc_bar_code.o lodepng/lodepng.o
TARGET = upc
CPP = g++

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS)

main.o: main.cpp
	$(CPP) -c -o main.o main.cpp -Wall -Wextra -pedantic -ansi -O3

upc_bar_code.o: upc_bar_code.cpp
	$(CPP) -c -o upc_bar_code.o upc_bar_code.cpp -Wall -Wextra -pedantic -ansi -O3

lodepng.o: lodepng/lodepng.cpp
	$(CPP) -c -o lodepng/lodepng.o lodepng/lodepng.cpp -Wall -Wextra -pedantic -ansi -O3

.PHONY: clean
clean:
	rm -f *.o *.exe lodepng/*.o
