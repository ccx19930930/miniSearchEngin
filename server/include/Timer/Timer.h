 ///
 /// @file    Timer.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 16:50:23
 ///

#ifndef __TIMER_H__
#define __TIMER_H__

#include "TimerConf.h"

#include <sys/timerfd.h>
#include <functional>

namespace ccx{

using std::function;

class Timer
{
	public:
		Timer();
		~Timer();
	public:
		uint64_t readTimefd();
		void start();
		void stop();
		int getTimerfd();
	private:
		void stopTimerfd();
		void setTimer(int initialTime, int intervalTime);
	private:
		int _timerfd;
		TimerConf _conf;
		bool _isStart;
	public:
		typedef function<void()> TimerCallback;
		void setTimeCallback(TimerCallback cb);
	private:
		TimerCallback _onTimerCallback;


};

}

#endif
