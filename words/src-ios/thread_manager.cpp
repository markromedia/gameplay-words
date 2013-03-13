//
//  thread_manager.cpp
//  words
//
//  Created by Mark Udit on 3/12/13.
//
//

#include "../src/thread_manager.hpp"
#include "ios_bridge.h"

ThreadManager* ThreadManager::instance = NULL;

void ThreadManager::PrintCurrentThreadName() {
    printThreadName();
}


