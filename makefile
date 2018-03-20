BM_DIR = basic-bitmap-fileio
include $(BM_DIR)/make_sm_vars
OBJECTS = main.o upc_bar_code.o $(BM_OBJECTS)
TARGET = upc.exe
CPP = g++

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS)

main.o: main.cpp
	$(CPP) -c -o main.o main.cpp

upc_bar_code.o: upc_bar_code.cpp
	$(CPP) -c -o upc_bar_code.o upc_bar_code.cpp

include $(BM_DIR)/make_sm_rules

.PHONY: clean
clean:
	rm -f *.o *.exe $(BM_DIR)/*.o
