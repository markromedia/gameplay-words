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
#include "../src/ext/solver_worker.hpp"
#include "../src/game/board/board_solver.hpp"

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
    BoardSolver::SolveBoard();
}

bool SolverWorker::IsRunning() {
    return isRunning();
}


#endif

