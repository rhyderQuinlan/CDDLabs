/**
 * @file main.cpp
 * @author Rhyder Quinlan
 * @brief 
 * This program prints out either the letter 'A' or 'B'
 * grouped by a shared variable and the number of threads (set to 100)
 * The barrierTask uses a reusable barrier to make sure all threads
 * run on one task (print A and shared_variable) before continuing
 * to the next task (Print B and shared_variable)
 * @version 0.1
 * @date 2019-11-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/**
 * @brief displays a message that is split in to 2 sections to show how a rendezvous works
 * 
 * @param theBarrier 
 * @param numLoops 
 */
void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Do first bit of task
    std::cout << "A"<< i;
    //Barrier
    theBarrier->initial_step();
    
    
    //Do second half of task
    std::cout<< "B" << i;

    //turn barrier
    theBarrier->final_step();
  }
}

/**
 * @brief creates a barrier (from barrier class) and demonstrates how it works with multiple threads.
 * 
 * @return int 
 */
int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(barrierTask,aBarrier,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
