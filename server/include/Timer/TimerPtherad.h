 ///
 /// @file    TimerPtherad.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 17:55:12
 ///

#ifndef __TIMERPTHREAD_H__
#define __TIMERPTHREAD_H__

#include "Timer.h"
#include "thread_pool/Pthread.h"

namespace ccx
{

class TimerPthread
{
	public:
		TimerPthread();
		void start();
		void stop();
		void setTimeCallback(Timer::TimerCallback cb);
	private:
		void TimerStart();
		Timer _timer;
		Pthread _pthread;
};

}

#endif
