 ///
 /// @file    QueryModule.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 20:58:20
 ///

#include "Cache/Cache.h"
#include "Query_module/QueryModule.h"
#include <math.h>
#include <json/json.h>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
namespace ccx{

using std::vector;
using std::set_intersection;
using std::map;
using std::bind;
using std::function;
using std::cout;
using std::endl;

QueryModule::QueryModule(Cache & cache)
: _data()
, _conf()
, _getdata(_data, _conf)
, _jieba()
, _cache(cache)
{
	_getdata.getPageData();
	cout << "QueryModule init success!" << endl;
}


void QueryModule::getFreq(map<string, int> & word_freq, vector<string> & words)
{
	vector<string>::iterator it_word;
	it_word = words.begin();
	for(; it_word != words.end(); ++it_word)
	{
		map<string, int>::iterator it_freq;
		it_freq = word_freq.find(*it_word);

		if(it_freq == word_freq.end())
		{
			pair<string, int> temp;
			temp.first = *it_word;
			temp.second = 1;
			word_freq.insert(temp);
		}else{
			++(it_freq->second);
		}
	}
}

void QueryModule::getData(list<Inv_pair> & it_inv, map<string, int> & words)
{
	map<string, int>::iterator it;
	it = words.begin();
	for(; it != words.end(); ++it)
	{
		Inv_pair inv_data;
		inv_data.first = it->first;
		int df = _data._dictionary.search(it->first, inv_data.second);
		WordMsg temp;
		temp._docid = 0;
		temp._freq = it->second;
		++df;
		int n = _data._items.size();
		double idf;
		idf = log2( (double)n * df);
		temp._weight = idf * it->second;
		inv_data.second.push_back(temp);
		it_inv.push_back(inv_data);
	}
}

void QueryModule::getElem(Elems & elems, list<Inv_pair> & it_inv)
{
	list<Inv_pair>::iterator it_list;
	it_list = it_inv.begin();
	for(; it_list != it_inv.end(); ++it_list)
	{
		pair<string, double> elem;
		elem.first = it_list->first;
		vector<WordMsg>::iterator it_vec;
		it_vec = it_list->second.begin();

		for(; it_vec != it_list->second.end(); ++it_vec)
		{
			Elems::iterator it_elem;
			it_elem = elems.find(it_vec->_docid);
			elem.second = it_vec->_weight;	
			if(it_elem == elems.end())
			{
				pair<int, map<string, double>  > temp;
				temp.first = it_vec->_docid;
				temp.second.insert(elem);
				elems.insert(temp);
			}else{
				it_elem->second.insert(elem);
			}
		}
	}
}

void QueryModule::getIntersection(vector<Elem> & data, Elems & elems, int num)
{
	Elems::iterator it_elem;
	it_elem = elems.begin();
	for(; it_elem != elems.end(); ++it_elem)
	{
		int size = it_elem->second.size();
		if(size >= num)
		{
			data.push_back(*it_elem);
		}
	}
}

bool sortRuleElem(pair<int, map<string, double > > & lhs, pair<int, map<string, double > > & rhs)
{
	return lhs.first < rhs.first;
}

bool sortRuleData(pair<int, double> & lhs, pair<int, double> & rhs)
{
	return lhs.second < rhs.second;
}


void QueryModule::elemSort(vector<Elem> & elem, vector<Data> & data)
{
	sort(elem.begin(), elem.end(), sortRuleElem);	
	
	vector<Elem>::iterator it_elem;
	it_elem = elem.begin();
	++it_elem;	

	for(; it_elem != elem.end(); ++it_elem)
	{
		double numerator = 0.0;
		double denominator = 0.0;
		double x = 0.0;
		double y = 0.0;
		
		map<string, double>::iterator it_temp1;
		map<string, double>::iterator it_temp2;
		
		it_temp1 = elem[0].second.begin();
		it_temp2 = it_elem->second.begin();

		for(; it_temp1 != elem[0].second.end(); ++it_temp1)
		{
			if(it_temp1->first == it_temp2->first)
			{
				x += (it_temp1->second * it_temp1->second);
				y += (it_temp2->second * it_temp2->second);
				numerator += (it_temp1->second * it_temp2->second);
				++ it_temp2;
			}
		}
		denominator = (sqrt(x) * sqrt(y));
		Data temp;
		temp.first = it_elem->first;
		temp.second = numerator / denominator;
		data.push_back(temp);
	}
	sort(data.begin(), data.end(), sortRuleData);
}


string QueryModule::unpack(vector<Data> & elems_sorted, vector<string> & words)
{

	Json::Value root;
	Json::Value person;

	vector<pair<int, double> >::iterator it_elem;
	it_elem = elems_sorted.begin();
	for(; it_elem != elems_sorted.end(); ++it_elem)
	{
		person["docid"] = _data._items[it_elem->first - 1].docid;
		person["title"] = _data._items[it_elem->first - 1].title;	
		person["link"] = _data._items[it_elem->first - 1].link;	

		string content = _data._items[it_elem->first - 1].content[0];

		string send = "...";
		bool flag = false;
		int num = 0;
		for(unsigned long i = 0; num < 3 && i < _data._items[it_elem->first - 1].content.size(); ++i)
		{
			size_t loc;
			vector<string>::iterator it_word;
			it_word = words.begin();
			for(; it_word != words.end(); ++it_word)
			{
				loc = _data._items[it_elem->first - 1].content[i].find(*it_word, 0);
				if(loc != string::npos)
				{
					flag = true;
					break;
				}
			}
			if(flag && num < 3)
			{
				string line =  _data._items[it_elem->first - 1].content[i];
				if(line.size() > 200)
				{
					string sub_line;
					if(loc > 100)
					{
						if(loc%2)
						{
							--loc;
						}
						sub_line = line.substr(loc - 50, 200);
					}else{
						sub_line = line.substr(0, 200);
					}
					send += sub_line;
				}else{
					send += line;
				}
				send += "...";
				flag = false;
				++num;
			}
		}

		person["content"] = send;

		root.append(person);
	}
	string data;
	Json::FastWriter writer;
	data = writer.write(root);
	return data;
}

string splitWords(vector<string> & data)
{
	vector<string>::iterator it;
	it = data.begin();
	string temp;	

	for(; it != data.end(); ++it)
	{
		temp += (*it);
	}
	return temp;
}

void QueryModule::do_Query(string & lhs, const string & rhs)
{
	vector<string> words;
	map<string, int> word_freq;
	_jieba.Cut_For_Search(rhs, words);

	if(words.size())
	{
		string temp = splitWords(words);

		bool flag;
		flag = _cache.Query(lhs, temp);
		if(!flag)
		{
			list<Inv_pair> it_inv;
			getFreq(word_freq, words);
			getData(it_inv, word_freq);
			if(it_inv.size())
			{
				Elems elems;
				getElem(elems, it_inv);
				vector<Elem> vec;
				getIntersection(vec, elems, words.size());
				
				vector<Data> data;
				elemSort(vec, data);
				lhs = unpack(data, words);
				CacheElem elem;
				elem._visit_num = 1;
				elem._data = lhs;
				pair<string, CacheElem> cache;
				cache.first = temp;
				cache.second = elem;
				_cache.pushData(cache);
			}
		}
	}
}
}
