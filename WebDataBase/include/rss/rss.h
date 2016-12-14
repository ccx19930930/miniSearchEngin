///
/// @file    rss.h
/// @author  chinxi(chenchengxi993@gmail.com)
/// @date    2016-10-27 17:12:42
///


#ifndef __RSS_H__
#define __RSS_H__

#include "tinyxml2.h"
#include "rssData.h"
#include <iostream>
#include <vector>

namespace ccx{

using tinyxml2::XMLDocument;
using std::string;
using std::vector;

class rssConf;
class RssReader
{
	public:
		RssReader(RssData & rssdata, rssConf & conf);
	public:
		void parse();
	private:
		void parseRss(const char * filename);//解析
		string replace(const char * data);
		RssData & _rssData;
		rssConf & _conf;
};   

}


#endif
