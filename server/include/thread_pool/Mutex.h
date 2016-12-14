 ///
 /// @file    Mutex.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 20:52:38
 ///


#ifndef __MUTEX_H__
#define __MUTEX_H__


#include "root/Noncopyable.h"

#include <pthread.h>

namespace ccx{


class Mutex
: private Noncopyable
{
	public:	
		Mutex();
		~Mutex();
		void lock();
		void unlock();
		pthread_mutex_t * getMutex();
	private:
		pthread_mutex_t _mutex;
};

}

#endif
