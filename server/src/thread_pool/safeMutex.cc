 ///
 /// @file    safeMutex.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 22:16:27
 ///


#include "thread_pool/safeMutex.h"


namespace ccx{

safeMutex::safeMutex(Mutex & mutex)
: _mutex(mutex)
{
	_mutex.lock();
}

safeMutex::~safeMutex()
{
	_mutex.unlock();
}

}
