 ///
 /// @file    PageLib.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 11:10:26
 ///


#ifndef __PAGELIB_H__
#define __PAGELIB_H__

#include "root/Noncopyable.h"
#include "rss/rssConf.h"
#include "rss/rssData.h"
#include "rss/RssOutput.h"
#include "rss/rss.h"
#include "rss/WordFrequency.h"
#include "rss/Repetition.h"
#include "rss/RssInvertindex.h"
#include "rss/MakeDictionary.h"

namespace ccx{

class PageLib
: private Noncopyable
{
	public:
		PageLib();
	
	public:
		void makePagLib();

	private:
		rssConf _conf;
		RssData _data;
		RssOutput _output;
		RssReader _rss;
		WordFrequency _word;
		Repetition _repet;
		RssInvertindex _inv;
		MakeDictionary _dictionary;
};
}

#endif
