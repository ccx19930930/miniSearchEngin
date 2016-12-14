 ///
 /// @file    GetConf.cc
 /// @author  ccx(chenchengxi993@gmail.com)
 /// @date    2016-11-24 10:58:43
 ///

#include "server/GetConf.h"

#include <stdlib.h>
#include <json/json.h>

#include <iostream>
#include <fstream>
#include <cassert>

namespace ccx{

using std::ifstream;
using std::cout;
using std::endl;

GetConf::GetConf()
{
	getConf();
}

void GetConf::getConf()
{
	ifstream ifs;	
	ifs.open("../conf/server/ServerConf.json");	
	if(!ifs.good())
	{
		cout << "open conf error" << endl;
		exit(EXIT_FAILURE);
	}
	Json::Reader reader;
	Json::Value root;
	if(!reader.parse(ifs, root, false))
	{
		cout << "Json error" << endl;
		exit(EXIT_FAILURE);
	}
	_IP = root["IP"].asString();
	_port = static_cast<uint16_t>(root["port"].asInt());
	_PthreadNum = root["PthreadNum"].asInt();
	_MaxQueueNum = root["MaxQueueNum"].asInt();
	
	cout << "read conf success!" << endl;
	cout << "IP : " << _IP << endl;
	cout << "port : " << _port << endl;
	cout << "PhtreadNum : " << _PthreadNum << endl;
	cout << "MaxQueueNum : " << _MaxQueueNum << endl;

	ifs.close();
}

string GetConf::getIP()
{
	return _IP;
}

uint16_t GetConf::getPort()
{
	return _port;
}

int GetConf::getPthreadNum()
{
	return _PthreadNum;
}

int GetConf::getMaxQueueNum()
{
	return _MaxQueueNum;
}

}
