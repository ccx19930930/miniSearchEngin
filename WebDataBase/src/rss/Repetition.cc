 ///
 /// @file    Repetition.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 14:52:08
 ///

#include "rss/Repetition.h"

#include <iostream>

namespace ccx{


Repetition::Repetition(RssData & data)
: _data(data)
{
}

void Repetition::Repet()
{
	divide();
	do_Repet();
}

bool Repetition::Repet_if(RssItemIt & it_lhs, RssItemIt & it_rhs)
{
	WordSortedIt it_lhs_word;
	const int max = 30;
	int sum = 0;

	it_lhs_word = it_lhs->wordmsg.begin();
	for(int i = 0; i < max && it_lhs_word != it_lhs->wordmsg.end(); ++it_lhs_word, ++i)
	{
		WordSortedIt it_rhs_word;
		it_rhs_word = it_rhs->wordmsg.begin();

		for(int j = 0;j < max && it_rhs_word != it_rhs->wordmsg.end(); ++it_rhs_word, ++j)
		{
			if(it_lhs_word->word == it_rhs_word->word)
			{
				++sum;
				break;
			}
		}
	}
	return sum >= (max * 80 / 100);
}

void Repetition::do_Repet()
{
	map<int, list<RssItemIt> >::iterator it_group;
	it_group = _data._group.begin();
	for(; it_group != _data._group.end(); ++it_group)
	{
		if(1 == it_group->second.size())//组内成员只有一个，不用去重
		{
			continue;
		}
		list<RssItemIt>::iterator it_list_base;
		it_list_base = it_group->second.begin();
		while(1)
		{
			if(it_list_base == it_group->second.end())
			{
				break;
			}
			RssItemIt it_rss_base;
			it_rss_base = *it_list_base;
			
			list<RssItemIt>::iterator it_list_cur;
			it_list_cur = it_list_base;
			
			while(1)
			{
				++it_list_cur;
				if(it_list_cur == it_group->second.end())
				{
					break;
				}
				RssItemIt it_rss_cur;
				it_rss_cur = *it_list_cur;
				if(Repet_if(it_rss_base, it_rss_cur))
				{
					list<RssItemIt>::iterator it_temp;
					it_temp = it_list_cur;
					--it_list_cur;
					it_group->second.erase(it_temp);
				}
			}
			++it_list_base;
		}
	}
}

void Repetition::divide()
{
	vector<RssItem>::iterator it_rss;
	it_rss = _data.items.begin();
	for(; it_rss != _data.items.end(); ++it_rss)
	{
		WordSortedIt it_word;
		it_word = it_rss->wordmsg.begin();
		int flag = 0;
		for(int i = 0; i < 10 && it_word != it_rss->wordmsg.end(); ++i, ++it_word)
		{
			flag ^= it_word->word[0];
		}
		map<int, list<RssItemIt> >::iterator it_temp;
		it_temp = _data._group.find(flag);
		if(it_temp == _data._group.end())
		{
			pair<int, list<RssItemIt> > temp;
			temp.first = flag;
			temp.second.push_back(it_rss);
			_data._group.insert(temp);
		}else{
			it_temp->second.push_back(it_rss);
		}
	}
}



}
