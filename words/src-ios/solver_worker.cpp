//
//  thread_manager.cpp
//  words
//
//  Created by Mark Udit on 3/12/13.
//
//
#ifdef __APPLE__
#include <sstream>

#include "ios_bridge.h"
#include "../src/solver_worker.hpp"
#include "../src/board_solver.hpp"

SolverWorker* SolverWorker::instance = NULL;

void SolverWorker::PrintCurrentThreadName() {
    printThreadName();
}

void SolverWorker::StartSolverWorker() {
    startWorkerThread();
}

void SolverWorker::StopWorker() {
    //block until worker thread completes
    stopWorkerThread();
    
    //release lock so worker can complete
    releaseWorkerLock();
}

void SolverWorker::PerformSolverTask() {
}


#endif

