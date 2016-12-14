 ///
 /// @file    TimerConf.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 17:25:39
 ///

#include "Timer/TimerConf.h"

#include <stdlib.h>
#include <json/json.h>

#include <iostream>
#include <fstream>

namespace ccx{

using std::ifstream;
using std::cout;
using std::endl;

TimerConf::TimerConf()
{
	GetConf();
}

void TimerConf::GetConf()
{
	ifstream ifs;
	ifs.open("../conf/server/TimerConf.json");
	if(!ifs.good())
	{
		cout << "open TimerConf error" << endl;
		exit(EXIT_FAILURE);
	}
	
	Json::Value root;
	Json::Reader reader;
	
	if(!reader.parse(ifs, root, false))
	{
		cout << "TimerConf reader parse error" << endl;
		exit(EXIT_FAILURE);
	}
	
	_initialTime = root["initialTime"].asInt();
	_intervalTime = root["intervalTime"].asInt();
}

int TimerConf::getInitialTime()
{
	return _initialTime;
}

int TimerConf::getIntervalTime()
{
	return _intervalTime;
}




}
