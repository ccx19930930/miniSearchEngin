 ///
 /// @file    PageConf.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 16:34:42
 ///

#ifndef __PAGECONF_H__
#define __PAGECONF_H__

#include <string>

namespace ccx{

using std::string;

class PageConf
{

	public:
		PageConf();
	private:
		void getConf();

	public:
		string getRipepagePath();
		string getOffsetPath();
		string getInvertindexPath();
	private:
		string _RipepagePath;
		string _OffsetPath;
		string _InvertindexPath;
};

}
#endif
