#Rhyder Quinlan, C00223030
# Lab 3:Rendezvous
#Output -> run
#Includes Semaphore.cpp and main.cpp


CC=g++
CFLAGS= -std=c++11 -pthread -O0

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: main.o
	$(CC) -o run Semaphore.cpp main.cpp $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o