 ///
 /// @file    Timer.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 17:01:41
 ///

#include "Timer/Timer.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include <iostream>

namespace ccx{

using std::endl;
using std::cout;

Timer::Timer()
: _timerfd(::timerfd_create(CLOCK_REALTIME, 0))
, _conf()
, _isStart(false)
{
	if(-1 == _timerfd)
	{
		perror("timerfd create");
		exit(EXIT_FAILURE);
	}	
}

Timer::~Timer()
{
	if(_isStart)
	{
		stop();
	}
}


uint64_t Timer::readTimefd()
{
	uint64_t howmany = 0;
	int ret = ::read(_timerfd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany))
	{
		cout << "read error!" << endl;
	}
	return howmany;
}

void Timer::start()
{
	setTimer(_conf.getInitialTime(), _conf.getIntervalTime());
	_isStart = true;

	struct pollfd pfd;
	pfd.fd = _timerfd;
	pfd.events = POLLIN;

	while(_isStart)
	{
		int ret = poll(&pfd, 1, 5000);
		if(-1 == ret)
		{
			if(errno == EINTR)
			{
				continue;
			}
			cout << "poll error" << endl;
			exit(EXIT_FAILURE);
		}
		if(0 == ret)
		{
			cout << "Timer poll timeout" << endl;
			continue;
		}
		if(pfd.revents & POLLIN)
		{
			readTimefd();
			if(_onTimerCallback)
			{
				_onTimerCallback();
			}
		}

	}


}

void Timer::stopTimerfd()
{
	setTimer(0, 0);
}

void Timer::stop()
{
	if(_isStart)
	{
		stopTimerfd();
		_isStart = false;
	}
}


void Timer::setTimer(int initialTime, int intervalTime)
{
	struct itimerspec value;
	value.it_value.tv_sec = initialTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = intervalTime;
	value.it_interval.tv_nsec = 0;
	int ret = ::timerfd_settime(_timerfd, 0, &value, NULL);
	if(-1 == ret)
	{
		cout << "timerfd_settime error!" << endl;
	}
}

int Timer::getTimerfd()
{
	return _timerfd;
}

void Timer::setTimeCallback(TimerCallback cb)
{
	_onTimerCallback = std::move(cb);
}



}
