 ///
 /// @file    WordFrequency.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 14:55:56
 ///


#ifndef __WORDFREQUENCY_H__
#define __WORDFREQUENCY_H__

#include "rssData.h"

namespace ccx{

class WordFrequency
{
	public:
		WordFrequency(RssData & data);
		void do_Count();
	private:
		RssData & _data;
};


}
#endif
