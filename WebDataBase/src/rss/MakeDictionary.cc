 ///
 /// @file    MakeDictionary.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-07 14:57:30
 ///

#include "rss/MakeDictionary.h"
#include <iostream>


namespace ccx{

using std::cout;
using std::endl;

MakeDictionary::MakeDictionary(RssData & data)
: _data(data)
{
}

void MakeDictionary::makeDictionary()
{
	GroupIt it_group;
	it_group = _data._group.begin();
	
	for(; it_group != _data._group.end(); ++it_group)
	{
		list<RssItemIt>::iterator it_list;
		it_list = (it_group->second).begin();
	
		for(; it_list != (it_group->second).end(); ++it_list)
		{
			RssItemIt it_rss;
			it_rss = *it_list;

			WordIt it_word;
			
			it_word = it_rss->wordmsg.begin();
			for(; it_word != it_rss->wordmsg.end(); ++it_word)
			{
				WordMsg msg;
				msg._docid = it_rss->docid;
				msg._freq = it_word->freq;
				msg._weight = it_word->weight;
				//cout << it_word->freq << "+++" << it_word->weight<< endl;
				_data._dictionary.push(it_word->word, msg);
			}
		}
	}
}

}
