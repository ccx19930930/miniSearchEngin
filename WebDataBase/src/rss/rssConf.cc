 ///
 /// @file    rssConf.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-28 11:51:02
 ///

#include "rss/rssConf.h"

#include <stdlib.h>
#include <json/json.h>
#include <iostream>
#include <fstream>

namespace ccx{

using std::ifstream;
using std::cout;
using std::endl;

rssConf::rssConf()
{
	getConf();
}

void rssConf::getConf()
{
	ifstream ifs;
	ifs.open("../conf/rss/rss.json");
	if(!ifs.good())
	{
		cout << "Jieba open conf error" << endl;
		exit(EXIT_FAILURE);
	}
	Json::Reader reader;
	Json::Value root;
	if(!reader.parse(ifs, root, false))
	{
		cout << "Json error" << endl;
		exit(EXIT_FAILURE);
	}
	
	_intputXmlPath = root["intputXmlPath"].asString();
	_outputRipepagePath = root["outputRipepagePath"].asString();
	_outputOffsetPath = root["outputOffsetPath"].asString();
	_outputInvertindexPath = root["outputInvertindexPath"].asString();

	_outputRssinitailPath = root["outputRssinitailPath"].asString();
	_outputWordfrequencyPath = root["outputWordfrequencyPath"].asString();
	_outputGroupmsgPath = root["outputGroupmsgPath"].asString();

}

string rssConf::getInputXmlPath()
{
	return _intputXmlPath;
}

string rssConf::getOutputRipepagePath()
{
	return _outputRipepagePath;
}

string rssConf::getOutputOffsetPath()
{
	return _outputOffsetPath;
}

string rssConf::getOutputInvertindexPath()
{
	return _outputInvertindexPath;
}

string rssConf::getOutputRssinitailPath()
{
	return _outputRssinitailPath;
}

string rssConf::getOutputWordfrequencyPath()
{
	return _outputWordfrequencyPath;
}

string rssConf::getOutputGroupmsgPath()
{
	return _outputGroupmsgPath;
}

}
