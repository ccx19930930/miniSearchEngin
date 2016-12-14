 ///
 /// @file    Cond.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 22:09:27
 ///


#include "thread_pool/Cond.h"


namespace ccx{


	Cond::Cond(Mutex & mutex)
	: _mutex(mutex)	
	{
		pthread_cond_init(&_cond, NULL);
	}
	
	Cond::~Cond()
	{
		pthread_cond_destroy(&_cond);
	}

	void Cond::wait()
	{
		pthread_cond_wait(&_cond, _mutex.getMutex());
	}

	void Cond::notify()
	{
		pthread_cond_signal(&_cond);
	}

	void Cond::notifyall()
	{
		pthread_cond_broadcast(&_cond);
	}

}
