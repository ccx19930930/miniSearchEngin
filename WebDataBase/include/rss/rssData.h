 ///
 /// @file    rssData.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 11:44:59
 ///


#ifndef __RSSDATA_H__
#define __RSSDATA_H__

#include <string>
#include <vector>
#include <map>
#include <list>

#include "Dictionary/Dictionary.h"

namespace ccx{ 
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::list;

struct Word
{
	string word;
	int docid;
	int freq;
	double weight;
};

struct RssItem
{
	int docid;
	string from;
	string title;
	string link;
	string content;
	vector<Word> wordmsg;
	map<string, int> wordfrequency;
};

struct RssData
{
	int doc_num;
	vector<RssItem> items;//原始数据
	map<int, list<vector<RssItem>::iterator> > _group;//分组依据:前10个高频词第一个字节数据按位异或
	map<string, int> _freqs;
	Dictionary _dictionary;//词典，可以存倒排索引信息
};   

}

#endif
