 ///
 /// @file    TimerConf.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 17:24:04
 ///


#ifndef __TIMERCONF_H__
#define __TIMERCONF_H__

namespace ccx{

class TimerConf
{
	public:
		TimerConf();
	
	public:
		int getInitialTime();
		int getIntervalTime();
	private:
		void GetConf();
	private:
		int _initialTime;
		int _intervalTime;

};

}
#endif
