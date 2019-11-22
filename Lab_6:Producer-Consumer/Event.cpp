#include "Event.h"
#include <iostream>
#include <stdlib.h>

/**
 * @brief Construct a new Event:: Event object
 * Randomly generate a lower case letter between a - z and print
 * 
 */
Event::Event(){
  /**< Generate random letter */
  letter = 'a' + rand() % 26;
  std::cout << letter;
}

/**
 * @brief convert generated lower case letter to uppercase ascii value and print
 * 
 */
void Event::consume(){
    /**< Convert letter to uppercase */
    char u_letter = letter - 32;    
    std::cout << u_letter;
}