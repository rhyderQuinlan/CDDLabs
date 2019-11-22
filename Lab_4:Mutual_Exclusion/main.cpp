/**
 * @file main.cpp
 * @author Rhyder Quinlan
 * @brief A demonstration of Mutual Exclusion
 * @version 0.1
 * @date 2019-11-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;

/**
 * @brief Demonstrates mutual exclusion with
 * the user of a shared variable
 * 
 * @param firstSem 
 * @param numUpdates 
 */
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){
  for(int i=0;i<numUpdates;i++){
    //UPDATE SHARED VARIABLE HERE!
    firstSem -> Wait();
    sharedVariable++;
    firstSem -> Signal();
  }

}

/**
 * @brief Creates 100 threads and a semaphore.
 * Loops through all threads and runs updateTask.
 * Prints out the value of sharedVariable.
 * 
 * @return int 
 */
int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1)); //Semaphore must be initialised to 1
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}


