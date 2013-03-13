#ifndef __THREAD_MANAGER__hpp
#define __THREAD_MANAGER__hpp

#include <string>

class ThreadManager
{
	/// @summary	singleton instance
	static ThreadManager* instance;
public:
	/// Simple utility to print the current threads name
	static void PrintCurrentThreadName();
};

#endif  // __THREAD_MANAGER__hpp