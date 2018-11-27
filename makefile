CC=g++
CFLAGS=-Wall
TARGET=exmax
CPPFILES=main.cpp ExpMax.cpp EM.cpp fileParser.cpp caseChange.cpp
HFILES=ExpMax.h EM.h fileParser.h caseChange.h

all: $(TARGET)

.PHONY: all clean

$(TARGET): $(CPPFILES) $(HFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(CPPFILES)

clean:
	$(RM) $(TARGET)