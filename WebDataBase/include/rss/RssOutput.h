 ///
 /// @file    RssOutput.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-27 21:44:00
 ///


#ifndef __RSSOUTPUT_H__
#define __RSSOUTPUT_H__

#include "rssData.h"
#include <fstream>

namespace ccx{

using std::ofstream;
class rssConf;
class RssOutput
{
	typedef vector<Word>::iterator WordSortedIt;
	typedef vector<RssItem>::iterator RssItemIt;
	typedef	map<int, list<vector<RssItem>::iterator> >::iterator GroupIt;
	typedef map<string, int>::iterator FreqIt;	
	public:
		RssOutput(RssData & data, rssConf & conf);
		
		void outputRssinitall();
		void outputWordfrequency();
		void outputGroupmsg();

		void outputRipepage();
		void outputInvertindex();
	private:
		RssData & _data;
		rssConf & _conf;
	private:
		int outputRss(ofstream & ofs, RssItemIt & it);
		void outputOffset(ofstream & ofs, RssItemIt & it);
		void outputWord(ofstream & ofs, RssItemIt & it);
};


}
#endif
