 ///
 /// @file    DictionaryConf.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-04 11:03:59
 ///

#include "Dictionary/DictionaryConf.h"
#include <json/json.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

namespace ccx{

using std::ifstream;
using std::cout;
using std::endl;

DictionaryConf::DictionaryConf()
{
	GetConf();
}

void DictionaryConf::GetConf()
{
	ifstream ifs;
	ifs.open("../conf/Dictionary/DictionaryConf.json");
	if(!ifs.good())
	{
		cout << "open DictionaryConf.json error" << endl;
		exit(EXIT_FAILURE); 
	}
	
	Json::Value root;
	Json::Reader reader;

	if(!reader.parse(ifs, root, false))
	{
		cout << "DictionaryConf json read error" << endl;
		exit(EXIT_FAILURE);
	}
	
	_DictionaryPath = root["DictionaryPath"].asString();
	
	ifs.close();
}

string DictionaryConf::getDictionaryPath()
{
	return _DictionaryPath;
}

}
