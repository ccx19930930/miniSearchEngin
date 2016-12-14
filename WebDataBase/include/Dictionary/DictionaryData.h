 ///
 /// @file    DictionaryData.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-03 10:16:51
 ///

#ifndef __DICTIONARYDATA_H__
#define __DICTIONARYDATA_H__

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

namespace ccx{

using std::string;
using std::unordered_map;
using std::shared_ptr;
using std::vector;

struct WordMsg
{
	int _docid;
	int _freq;
	double _weight;
};

struct DictElem
{
	int _Freq;//词频，如果是根结点，则为0
	string _word;//如果是根结点，则填ROOT
	vector<WordMsg> _msg;
	unordered_map<string, shared_ptr<DictElem> > _words;
};

typedef shared_ptr<DictElem> pDictElem;

}

#endif
