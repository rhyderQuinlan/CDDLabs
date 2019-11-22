/**
 * @file main.cpp
 * @author Rhyder Quinlan
 * @brief An Implementation of Threads Using Semaphores. Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions
 * @version 0.1
 * @date 2019-11-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

/** @fn taskOne
 * @brief Will run after delay and print message first
 * @param shared_ptr<Semaphore> theSemaphore
 * @param int delay
 */ 

/*! displays a message first*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore -> Signal();
}

/** @fn taskTwo
 * @brief Forced to wait for taskOne to complete and print message second
 * @param shared_ptr<Semaphore> theSemaphore
 */ 
/*! displays a message second*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore -> Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

/** @fn main
 * @brief Will initialise two threads and a semaphore
          Then run taskOne and taskTwo
          and join the threads afterwards.
 */ 

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
