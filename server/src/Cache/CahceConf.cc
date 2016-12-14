 ///
 /// @file    CahceConf.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-02 16:55:22
 ///

#include "Cache/CacheConf.h"

#include <stdlib.h>
#include <json/json.h>

#include <iostream>
#include <fstream>


namespace ccx{

using std::ifstream;
using std::cout;
using std::endl;

CacheConf::CacheConf()
{
	GetConf();
}

void CacheConf::GetConf()
{
	ifstream ifs;
	ifs.open("../conf/server/CacheConf.json");
	if(!ifs.good())
	{
		cout << "open CacheConf.json error" << endl;
		exit(EXIT_FAILURE);
	}
	
	Json::Value root;
	Json::Reader reader;

	if(!reader.parse(ifs, root, false))
	{
		cout << "CacheConf reader parse error" << endl;
		exit(EXIT_FAILURE);
	}
	
	_cachePath = root["CachePath"].asString();
	
	ifs.close();
}

string CacheConf::getCachePath()
{
	return _cachePath;
}

}
