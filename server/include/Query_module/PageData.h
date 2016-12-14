 ///
 /// @file    PageData.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 16:22:40
 ///

#ifndef __PAGEDATA_H__
#define __PAGEDATA_H__


#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include "Dictionary/Dictionary.h"

namespace ccx{

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;
using std::list;

struct RssItem
{
	int docid;
	string title;
	string link;
	vector<string> content;
};

#if 0
struct Invertindex//倒排索引
{
	int docid;
	int freq;
	double weight;
};
#endif

struct Offset
{
	int docid;
	int length;
	int offset;
};

struct PageData
{
	vector<RssItem> _items;//网页库
	vector<Offset> _offset;//偏移表
//	unordered_map<string, vector<Invertindex> > _invertindex;//倒排索引表
	Dictionary _dictionary;
};   



}

#endif
