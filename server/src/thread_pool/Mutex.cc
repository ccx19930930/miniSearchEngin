 ///
 /// @file    Mutex.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 22:03:33
 ///


#include "thread_pool/Mutex.h"

namespace ccx{

Mutex::Mutex()
{
	pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&_mutex);
}

void Mutex::lock()
{
	pthread_mutex_lock(&_mutex);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t * Mutex::getMutex()
{
	return &_mutex;
}

}
