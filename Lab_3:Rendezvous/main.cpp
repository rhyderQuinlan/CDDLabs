/**
 * @file main.cpp
 * @author Rhyder Quinlan C00223030
 * @brief Working with rendezvous points.
 * @version 0.1
 * @date 2019-11-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  firstSem->Signal();
  //THIS IS THE RENDEZVOUS POINT!
  secondSem->Wait();
  std::cout << "Task One has left!"<<std::endl;
}
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  secondSem->Signal();
  //THIS IS THE RENDEZVOUS POINT!
  firstSem->Wait();
  std::cout << "Task Two has left "<<std::endl;
}

/**
 * @brief Creates 2 semaphores and 2 threads.
 * Running taskOne and taskTwo will show how a rendezvous
 * makes all threads wait until all are ready together
 * to continue.
 * 
 * @return int 
 */
int main(void){
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore(1));
  int taskOneDelay = 3;
  int taskTwoDelay = 1;
  /**< Launch the threads  */

  std::thread ThreadOne = std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  std::thread ThreadTwo = std::thread(taskOne,sem1,sem2,taskOneDelay);
  
  std::cout << "Launched from the main\n";
  ThreadOne.join();
  ThreadTwo.join();

  return 0;
}
