 ///
 /// @file    Repetition.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 14:50:06
 ///


#ifndef __REPETITION_H__
#define __REPETITION_H__

#include "rssData.h"

#include <map>
#include <set>

namespace ccx{

using std::map;
using std::set;

class Repetition
{
	typedef vector<Word>::iterator WordSortedIt;
	typedef vector<RssItem>::iterator RssItemIt;
	typedef	map<int, set<vector<RssItem>::iterator> >::iterator GroupIt;
	public:
		Repetition(RssData & data);
		void Repet();
	private:
		void divide();//分组
		void do_Repet();
		bool Repet_if(RssItemIt & it_lhs, RssItemIt & it_rhs);
	private:
		RssData & _data;
};

}
#endif
