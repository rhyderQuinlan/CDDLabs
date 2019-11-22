/**
 * @file main.cpp
 * @author Rhyder Quinlan
 * @brief Demonstration of producers and consumers.
 * @version 0.1
 * @date 2019-11-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Event.h"
#include "SafeBuffer.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
const int size=20;


/**
 * @brief Initialises event and pushes to buffer (b)
 * 
 * @param b 
 * @param numLoops 
 */
void producer(std::shared_ptr<SafeBuffer> b, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Produce event and add to buffer
    Event event ;
    b->push(event);
  }
  

}

/**
 * @brief consumes (pops) next event on buffer (b)
 * 
 * @param b 
 * @param numLoops 
 */
void consumer(std::shared_ptr<SafeBuffer> b, int numLoops){

  for(int i=0;i<numLoops;++i){
    Event event ;
    event = b->pop();
    event.consume();
  }

}

/**
 * @brief Creates two vectors of producers and consumers and a buffer of the SafeBuffer class.
 * Demonstration of threads events being produced and consumed.
 * 
 * @return int 
 */
int main(void){

  std::vector<std::thread> producers(num_threads);
  std::vector<std::thread> consumers(num_threads);
  std::shared_ptr<SafeBuffer> buffer( new SafeBuffer());

  /**< Launch the threads  */
  for(std::thread& p: producers){
    p=std::thread(producer,buffer,10);
  }

  for(std::thread& c: consumers){
    c=std::thread(consumer,buffer,10);
  }
  
  /**< Join the threads with the main thread */
  for (auto& p :producers){
      p.join();
  }
  for (auto& c :consumers){
      c.join();
  }

  std::cout << std::endl;
  return 0;
}
