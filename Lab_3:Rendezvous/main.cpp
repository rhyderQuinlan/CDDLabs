#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \class Signal
    \brief An Implementation of a Rendezvous using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  theMutex->Wait();
  counter++;
  if(counter == 10){
    otherSemaphore->Wait();
    theSemaphore->Signal();
  }
  theMutex->Signal();
  theSemaphore->Wait();
  theSemaphore->Signal();

  std::cout << "Task One has left!"<<std::endl;

  theMutex->Wait();
  counter--;
  if(counter == 0){
    theSemaphore->Wait();
    otherSemaphore->Signal();
  }
  theMutex->Signal();
  otherSemaphore->Wait();
  otherSemaphore->Signal();
}
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  std::cout << "Task Two has left "<<std::endl;
}

int main(void){
  std::thread threadArray[10];
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore(1));
  std::shared_ptr<Semaphore> mutex1( new Semaphore);
  mutex1->Signal();
  /**< Launch the threads  */
  for (int i = 0; i < 10; ++i)
  {
    threadArray[i]=std::thread(taskOne, sem1, mutex1, sem2);
  }
  std::cout << "Launched from the main\n";
  for (int i = 0; i < 10; ++i)
  {
    threadArray[i].join();
  }
  return 0;
}
