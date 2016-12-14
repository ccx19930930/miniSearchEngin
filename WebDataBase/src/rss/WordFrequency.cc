 ///
 /// @file    WordFrequency.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 14:57:27
 ///

#include "rss/WordFrequency.h"
#include "CppJieba/Cppjieba.h"

//#include <boost/regex.hpp>

#include <ctype.h>

#include <iostream>
#include <algorithm>


namespace ccx{

using std::cout;
using std::endl;
using std::pair;
using std::sort;

WordFrequency::WordFrequency(RssData & data)
: _data(data)
{
}

bool compare(Word & lhs, Word & rhs)
{
	return lhs.freq > rhs.freq;
}


void WordFrequency::do_Count()
{
	Cppjieba jieba;

	vector<RssItem>::iterator it_rss;
	it_rss = _data.items.begin();
	
	vector<string>::iterator it_jieba;

	for(; it_rss != _data.items.end(); ++it_rss)
	{
		string data = it_rss->content;
		jieba.Cut_For_Search(data);
		it_jieba = jieba.getWord();	
		for(int i = 0; i < jieba.getWordSize(); ++i)
		{
			map<string, int>::iterator it_temp;
			it_temp = it_rss->wordfrequency.find(*it_jieba);
			if(it_temp == it_rss->wordfrequency.end())
			{
				pair<string, int> temp;
				temp.first = *it_jieba;
				temp.second = 1;
				it_rss->wordfrequency.insert(temp);
			}else{
				++(it_temp->second);
			}
			++it_jieba;
		}
		for(auto & elem : it_rss->wordfrequency)
		{
			Word temp;
			temp.word = elem.first;
			temp.freq = elem.second;
			temp.weight = 0.0;
			it_rss->wordmsg.push_back(temp);
		}
		sort(it_rss->wordmsg.begin(),
					it_rss->wordmsg.end(),
					compare);
	}
}


}
