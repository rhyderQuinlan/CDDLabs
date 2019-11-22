#include "SafeBuffer.h"
#include <iostream>
#include <stdlib.h>
#include "Event.h"

/**
 * @brief Construct a new Safe Buffer:: Safe Buffer object
 * 
 */
SafeBuffer::SafeBuffer(){
    Mutex = std::make_shared<Semaphore>(1);
    Sem = std::make_shared<Semaphore>(0);
}

/**
 * @brief push Method
 * 
 * @param newChar 
 * @return int 
 */
int SafeBuffer::push(Event generate){
    Mutex->Wait();
    Data.push_back(generate);
    int size = Data.size();
    Mutex->Signal();
    Sem->Signal();
    return size;
}

/**
 * @brief pop method
 * 
 * @return Event 
 */
Event SafeBuffer::pop(){
    Sem->Wait();
    Mutex->Wait();
    Event e = Data.back();
    Data.pop_back();
    Mutex->Signal();
    return e;
}