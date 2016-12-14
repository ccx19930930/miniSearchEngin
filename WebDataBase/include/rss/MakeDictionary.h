 ///
 /// @file    MakeDictionary.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-07 14:57:30
 ///

#ifndef __MAKEDICTIONARY_H__
#define __MAKEDICTIONARY_H__

#include "rssData.h"

namespace ccx{

class MakeDictionary
{
	typedef vector<Word>::iterator WordIt;
	typedef vector<RssItem>::iterator RssItemIt;
	typedef	map<int, list<vector<RssItem>::iterator> >::iterator GroupIt;
	typedef map<string, int>::iterator FreqIt;	
	public:
		MakeDictionary(RssData & data);
		void makeDictionary();
	private:
		RssData & _data;
};
}

#endif
