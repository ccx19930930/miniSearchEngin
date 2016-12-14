 ///
 /// @file    CacheConf.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-02 16:53:50
 ///


#ifndef __CACHECONF_H__
#define __CACHECONF_H__

#include <string>

namespace ccx{

using std::string;

class CacheConf
{
	public:
		CacheConf();
		void GetConf();
		string getCachePath();
	private:
		string _cachePath;
};

}
#endif
