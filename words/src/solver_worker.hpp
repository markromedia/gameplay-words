#ifndef __THREAD_MANAGER__hpp
#define __THREAD_MANAGER__hpp

#include <string>

class SolverWorker
{
public:
	/// @summary	singleton instance
	static SolverWorker* instance;

	/// Simple utility to print the current threads name
	static void PrintCurrentThreadName();
    
    // starts the worker thread (might create an instance of this class the job)
    static void StartSolverWorker();
    
    // stops the worker
    static void StopWorker();
    
    // preforms the solver task (in a thread)
    void PerformSolverTask();
};

#endif  // __THREAD_MANAGER__hpp