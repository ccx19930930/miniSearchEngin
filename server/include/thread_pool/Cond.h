 ///
 /// @file    Cond.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 21:00:47
 ///


#ifndef __COND_H__
#define __COND_H__

#include "Mutex.h"
#include "root/Noncopyable.h"

#include <pthread.h>


namespace ccx{

class Cond
: private Noncopyable
{
	public:
		Cond(Mutex & mutes);
		~Cond();
		void notify();
		void notifyall();
		void wait();
	private:
		Mutex & _mutex;
		pthread_cond_t _cond;
};

}

#endif
