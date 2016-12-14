 ///
 /// @file    RssInvertindex.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-28 15:25:14
 ///

#ifndef __INVERTINDEX_H__
#define __INVERTINDEX_H__

#include "rssData.h"

namespace ccx{

class RssInvertindex
{
	typedef vector<Word>::iterator WordSortedIt;
	typedef vector<RssItem>::iterator RssItemIt;
	typedef	map<int, list<vector<RssItem>::iterator> >::iterator GroupIt;
	typedef map<string, int>::iterator FreqIt;	
	public:
		RssInvertindex(RssData & data);
	public:
		void makeInvertindex();
	private:
		void count();
	private:
		RssData & _data;
};

}


#endif
