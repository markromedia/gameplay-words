#ifndef __THREAD_MANAGER__hpp
#define __THREAD_MANAGER__hpp

#include <string>

class SolverWorker
{
private:
	//whether or not its running
	static bool is_running;
public:
	/// @summary	singleton instance
	static SolverWorker* instance;

	/// Simple utility to print the current threads name
	static void PrintCurrentThreadName();
    
    // starts the worker thread (might create an instance of this class the job)
    static void StartSolverWorker();
    
    // stops the worker
    static void StopWorker();

	/// Query if this object is running.
	/// @return	true if running, false if not.
	static bool IsRunning();
    
    // preforms the solver task (in a thread)
    void PerformSolverTask();
};

#endif  // __THREAD_MANAGER__hpp