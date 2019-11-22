#Rhyder Quinlan, C00223030
# Lab 6: Producer-Consumer
#Output -> main
#Includes Semaphore.cpp and main.cpp


CC=g++
CFLAGS= -std=c++11 -pthread -O0

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: main.o
	$(CC) -o main SafeBuffer.cpp Event.cpp Semaphore.cpp main.cpp $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG -Wall
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o

#this generates the doxygen documentation using the <config file>
DOC:
	doxygen Doxyfile