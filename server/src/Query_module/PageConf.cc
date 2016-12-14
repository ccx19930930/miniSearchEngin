 ///
 /// @file    PageConf.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 16:42:55
 ///


#include "Query_module/PageConf.h"

#include <stdlib.h>
#include <json/json.h>

#include <iostream>
#include <fstream>


namespace ccx{

using std::ifstream;
using std::cout;
using std::endl;

PageConf::PageConf()
{
	getConf();
}


void PageConf::getConf()
{
	Json::Value root;
	Json::Reader reader;

	ifstream ifs;
	ifs.open("../conf/server/PageConf.json");	
	if(!ifs.good())
	{
		cout << "open PageConf.json error" << endl;
		exit(EXIT_FAILURE);
	}
	
	if(!reader.parse(ifs, root, false))
	{
		cout << "json reader parse error" << endl;
		exit(EXIT_FAILURE);
	}
	
	_RipepagePath = root["RipepagePath"].asString();
	_OffsetPath = root["OffsetPath"].asString();
	_InvertindexPath = root["InvertindexPath"].asString();
	ifs.close();

}


string PageConf::getRipepagePath()
{
	return _RipepagePath;
}

string PageConf::getOffsetPath()
{
	return _OffsetPath;
}

string PageConf::getInvertindexPath()
{
	return _InvertindexPath;
}

}
