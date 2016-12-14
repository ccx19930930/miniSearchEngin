 ///
 /// @file    RssInvertindex.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-28 15:28:56
 ///

#include "rss/RssInvertindex.h"

#include <math.h>

#include <iostream>

namespace ccx{

using std::cout;
using std::endl;

RssInvertindex::RssInvertindex(RssData & data)
: _data(data)
{
}

void RssInvertindex::count()
{
	GroupIt it_group;
	it_group = _data._group.begin();

	int docid = 1;

	for(; it_group != _data._group.end(); ++it_group)
	{
		list<RssItemIt>::iterator it_list;
		it_list = it_group->second.begin();
			
		for(; it_list != it_group->second.end(); ++it_list)
		{
			RssItemIt it_rss;
			it_rss = *it_list;
			
			WordSortedIt it_word;
			it_word = it_rss->wordmsg.begin();
			
			

			it_rss->docid = docid;
			++docid;

			for(; it_word != it_rss->wordmsg.end(); ++it_word)
			{
				FreqIt it_inv;
				it_inv = _data._freqs.find(it_word->word);

				if(it_inv == _data._freqs.end())
				{
					pair<string, int> temp;
					temp.first = it_word->word;
					temp.second = 1;
					_data._freqs.insert(temp);
				}else{
					++(it_inv->second);
				}
			}
		}
	}
	_data.doc_num = docid - 1;
}


#if 0
void RssInvertindex::makeInvertindex()
{
	count();
	FreqIt it_inv;
	it_inv = _data._invertindex.begin();

	for(; it_inv != _data._invertindex.end(); ++it_inv)
	{
		vector<Invertindex>::iterator it_vec;
		it_vec = it_inv->second.begin();
		
		int df = it_inv->second.size();
		double idf;
		idf = log( (double)_data.doc_num / df );
		double weight_sum = 0.0;
		for(; it_vec != it_inv->second.end(); ++it_vec)
		{
			it_vec->weight_temp = idf * it_vec->freq;
			weight_sum += (it_vec->weight_temp * it_vec->weight_temp);
		}
		double weight_sqrt;	
		weight_sqrt = sqrt(weight_sum);
		for(it_vec = it_inv->second.begin(); it_vec != it_inv->second.end(); ++it_vec)
		{
		//	it_vec->weight = it_vec->weight_temp / weight_sqrt;
			it_vec->weight = it_vec->weight_temp;
		}
	}
}

#endif

void RssInvertindex::makeInvertindex()
{
	count();
	GroupIt it_group;
	it_group = _data._group.begin();

	for(; it_group != _data._group.end(); ++it_group)
	{
		list<RssItemIt>::iterator it_list;
		it_list = it_group->second.begin();
			
		for(; it_list != it_group->second.end(); ++it_list)
		{
			RssItemIt it_rss;
			it_rss = *it_list;
			int size = it_rss->wordmsg.size();
			double weight_sum = 0.0;
			for(int i = 0; i < size; ++i)
			{
				int df = _data._freqs[it_rss->wordmsg[i].word];
				double idf;
				idf = log2( (double)_data.doc_num / df );
				//cout << idf << " = log2 ( " << _data.doc_num << " / " << df << " ) " << endl;
				double weight = idf * it_rss->wordmsg[i].freq;
				//cout << weight << " = " << idf << " * " << it_rss->wordmsg[i].freq << endl;
				it_rss->wordmsg[i].weight = weight;
				weight_sum += weight;
			}
			for(int i = 0; i < size; ++i)
			{
				//cout << it_rss->wordmsg[i].weight << " / " << weight_sum;
				it_rss->wordmsg[i].weight /= weight_sum;
				//cout << " = " << it_rss->wordmsg[i].weight << endl;
			}
		}
	}
}

}
