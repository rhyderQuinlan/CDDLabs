/**
 * @file barrier.cpp
 * @author Rhyder Quinlan
 * @brief A Barrier instance used within main
 * @version 0.1
 * @date 2019-11-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */

// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: 
// Author: Joseph Kehoe, Rhyder Quinlan
// Maintainer: 
// Created: Tue Jan  8 12:14:02 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Tue Jan  8 12:15:21 2019 (+0000)
//           By: Joseph
//     Update #: 2
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>

//constructor method
/**
 * @brief Construct a new Barrier:: Barrier object
 * 
 * @param numThreads 
 */
Barrier::Barrier(int numThreads)
{
    this->numThreads = numThreads;
    current_count = 0;
    lock.reset(new Semaphore(1));
    t_one.reset(new Semaphore(0));
    t_two.reset(new Semaphore(1));
}

//Destructor method
/**
 * @brief Destroy the Barrier:: Barrier object
 * 
 */
Barrier::~Barrier()
{
    lock.reset();
    t_one.reset();
    t_two.reset();
    std::cout << "Run Destructor complete" << std::endl;
}

/**
 * @brief Trigger initial_step and final_step
 * 
 */
void Barrier::wait()
{
    initial_step();
    final_step();
}

void Barrier::initial_step()
{
    lock->Wait();
    ++current_count;
    if (current_count == numThreads)
    {
        t_two->Wait();
        t_one->Signal();
    }
    lock->Signal();
    t_one->Wait();
    t_one->Signal();
}

void Barrier::final_step()
{
    lock->Wait();
    --current_count;
    if (current_count == 0)
    {
        t_one->Wait();
        t_two->Signal();
    }
    lock->Signal();
    t_two->Wait();
    t_two->Signal();
}

// 
// Barrier.cpp ends here
