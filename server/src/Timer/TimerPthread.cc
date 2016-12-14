 ///
 /// @file    TimerPthread.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 17:56:15
 ///

#include "Timer/TimerPtherad.h"


#include <functional>

namespace ccx{

using std::bind;

TimerPthread::TimerPthread()
: _timer()
, _pthread(bind(&TimerPthread::TimerStart, this))
{
}


void TimerPthread::TimerStart()
{
	_timer.start(); 
}

void TimerPthread::start()
{
	_pthread.start();
}

void TimerPthread::stop()
{
	_timer.stop();
	_pthread.join();
}

void TimerPthread::setTimeCallback(Timer::TimerCallback cb)
{
	_timer.setTimeCallback(cb);
}

}
