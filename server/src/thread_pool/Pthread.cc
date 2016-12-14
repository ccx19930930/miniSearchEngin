 ///
 /// @file    Pthread.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-16 10:55:34
 ///


#include "thread_pool/Pthread.h"

#include <iostream>

namespace ccx{

using std::cout;
using std::endl;


Pthread::Pthread(function<void() > func)
: _pthid(0)
, _isrunning(false)
, _func(func)
{
}

Pthread::~Pthread()
{
	if(_isrunning)
	{
		pthread_detach(_pthid);
	}
}

void Pthread::clean(void * )
{
	cout << pthread_self() << " >>>>>>>> exit!" << endl;
}


void * Pthread::fun(void *v)
{
	pthread_cleanup_push(Pthread::clean, NULL);
	Pthread * p = static_cast<Pthread*> (v);
	p->_func();
	pthread_exit(NULL);
	pthread_cleanup_pop(0);
}

void Pthread::join()
{
	if(_isrunning)
	{
		pthread_join(_pthid, NULL);
	}
	_isrunning = false;
}

void Pthread::start()
{
	pthread_create(&_pthid, NULL, Pthread::fun, this);
	_isrunning = true;
}


#if 0
void Pthread::stop()
{
	if(_isrunning)
	{
	//	pthread_cancel(_pthid);
	}
}
#endif

}
