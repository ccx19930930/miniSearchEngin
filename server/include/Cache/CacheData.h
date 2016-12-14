 ///
 /// @file    CacheData.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 23:02:02
 ///


#ifndef __CACHEDATA_H__
#define __CACHEDATA_H__

#include <string>
#include <unordered_map>

namespace ccx{

using std::string;
using std::unordered_map;

struct CacheElem
{
	int _visit_num;	
	string _data;
};

struct CacheData
{
	unordered_map<string, CacheElem> _cache;	
};

}



#endif
