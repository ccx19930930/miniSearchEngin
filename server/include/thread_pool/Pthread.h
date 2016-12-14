 ///
 /// @file    Pthread.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 20:37:19
 ///

#ifndef __PTHREAD_H__
#define __PTHREAD_H__


#include "root/Noncopyable.h"
#include "Buffer.h"
#include "Task.h"
#include <pthread.h>
#include <functional>


namespace ccx{

using std::function;


typedef Task DATA;

class Pthread
: private Noncopyable
{
	public:
		Pthread(function<void() > func);
		virtual ~Pthread();
		void start();
//		void stop();
		void join();
	private:
		static void * fun(void * v);
		static void clean(void * );
		pthread_t _pthid;
		bool _isrunning;
		function<void() > _func;
};


}


#endif
