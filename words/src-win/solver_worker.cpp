#include "../src/solver_worker.hpp"

#include <sstream>
#include <boost/thread.hpp>   
#include <boost/date_time.hpp>       

#include "gameplay.h"

SolverWorker* SolverWorker::instance = NULL;

//the mutex lock
boost::mutex mutex;
//the state of the bool
bool is_running;

long count;

void solverFunc() {
	SolverWorker::instance->PerformSolverTask();
}

/// Simple utility to print the current threads name
void SolverWorker::PrintCurrentThreadName() {
}

// starts the worker thread (might create an instance of this class the job)
void SolverWorker::StartSolverWorker() {
	//lazy load the runner
	if (instance == NULL) {
		instance = new SolverWorker;
	}

	count = 0;
	is_running = true;
	
	//probably should use a pool, since creates new thread every time. might
	//not be the most efficient to keep creating threads every secondish
	boost::thread solver_worker(solverFunc);
	solver_worker.detach();
}

// stops the worker
void SolverWorker::StopWorker() {
	mutex.lock();
	is_running = false;
	mutex.unlock();

	std::stringstream ss;
	ss << "ran " << count << " iterations inside thread\n";
	gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, ss.str().c_str());
}

// preforms the solver task (in a thread)
void SolverWorker::PerformSolverTask() {
	while (is_running) {
		mutex.lock();
		//might not still be running, so make sure
		if (is_running) {
			//solve a board
			count++;
		}
		mutex.unlock();
	}
}
