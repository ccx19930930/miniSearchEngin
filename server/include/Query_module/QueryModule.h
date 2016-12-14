 ///
 /// @file    QueryModule.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 20:56:29
 ///

#ifndef __QUERYMODULE_H__
#define __QUERYMODULE_H__

#include "GetPageData.h"
#include "PageConf.h"
#include "PageData.h"
#include "CppJieba/Cppjieba.h"


#include <map>

namespace ccx{

using std::map;


class Cache;
class QueryModule
{
	typedef pair<string, vector<WordMsg> > Inv_pair;
	typedef map<int, map<string, double > > Elems;
	typedef pair<int, map<string, double > > Elem;
	typedef pair<int, double> Data;
	public:
		QueryModule(Cache & cache);
	private:
		PageData _data;
		PageConf _conf;
		GetPageData _getdata;
		Cppjieba _jieba;
		Cache & _cache;

	public:
		void do_Query(string & lhs, const string & rhs);
	private:
		void getFreq(map<string, int> & word_freq, vector<string> & words);//获得查询词内的词频
		void getData(list<Inv_pair> & inv, map<string, int> & word_freq);//从词典中取数据,并计算出BASE
		void getElem(Elems & elems, list<Inv_pair> & inv);//信息整理
		void getIntersection(vector<Elem> & data, Elems & elems, int num);//取交集，num为最少匹配词数
		void elemSort(vector<Elem> & elem, vector<Data> & data);//文章排序
		string unpack(vector<Data> & elems_sorted, vector<string> & words);

};

}
#endif
