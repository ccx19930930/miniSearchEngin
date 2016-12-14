 ///
 /// @file    GetConf.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-24 10:54:12
 ///

#ifndef __GETCONF_H__
#define __GETCONF_H__

#include <string>
namespace ccx{

using std::string;

class GetConf
{
	public:
		GetConf();
		
		void getConf();
		
		string getIP();
		uint16_t getPort();
		int getPthreadNum();
		int getMaxQueueNum();
	private:
		string _IP;
		uint16_t _port;
		int _PthreadNum;
		int _MaxQueueNum;
};

}

#endif
