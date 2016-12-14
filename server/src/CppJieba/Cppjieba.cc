 ///
 /// @file    Cppjieba.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 10:14:03
 ///
 
#include "CppJieba/Cppjieba.h"
#include "CppJieba/CppjiebaConf.h"

#include <boost/regex.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>

namespace ccx{

using std::cout;
using std::endl;
using std::ifstream;
using std::bind;
using std::remove_if;
using std::function;

Cppjieba::Cppjieba()
: _conf()
, _jieba(
		_conf.get_DICT_PATH(),
		_conf.get_HMM_PATH(),
		_conf.get_USER_DICT_PATH(),
		_conf.get_IDF_PATH(),
		_conf.get_STOP_WORD_PATH()
		)
{
#ifdef NEED_REMOVE_STOP
	getStopWords();
#endif
}

#if 0
vector<string>::iterator Cppjieba::getWord()
{
#ifdef NEED_REMOVE_STOP
#endif
	return _words.begin();
}

ssize_t Cppjieba::getWordSize()
{
	return _words.size();
}
#endif

vector<cppjieba::Word>::iterator Cppjieba::getJiebaWord()
{
	return _jiebawords.begin();
}

ssize_t Cppjieba::getJiebaWordSize()
{
	return _jiebawords.size();
}

void Cppjieba::Cut_With_Hmm(const string & data, vector<string> & words)
{
	_jieba.Cut(data, words, true);
	removeStopWords(words);
}

void Cppjieba::Cut_Without_Hmm(const string & data, vector<string> & words)
{
	_jieba.Cut(data, words, false);
	removeStopWords(words);
}

void Cppjieba::Cut_All(const string & data, vector<string> & words)
{
	_jieba.CutAll(data, words);
	removeStopWords(words);
}

void Cppjieba::Cut_For_Search(const string & data, vector<string> & words)
{
	_jieba.CutForSearch(data, words);
	removeStopWords(words);
}

void Cppjieba::Insert_User_Word(const string & data)
{
	_jieba.InsertUserWord(data);
}

void Cppjieba::Cut_For_Search_Word_With_Offset(const string & data)
{
	_jieba.CutForSearch(data, _jiebawords, true);
}

void Cppjieba::Lookup_Tag_For_Single_Token()
{
	cout << "不知道干嘛用的没封装 : Lookup_Tag_For_Single_Token" << endl;
}

void Cppjieba::Tagging()
{
	cout << "不知道干嘛用的没封装 : Tagging" << endl;
}

void Cppjieba::Keyword_Extraction()
{
	cout << "不知道干嘛用的没封装 : Keyword_Extraction" << endl;
}

#ifdef NEED_REMOVE_STOP
void Cppjieba::getStopWords()
{
	ifstream ifs;
	ifs.open(_conf.get_STOP_WORD_PATH());
	if(!ifs.good())
	{
		cout << "open stop words file error" << endl;
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		if(!ifs.good())
		{
			break;
		}
		string s;
		getline(ifs, s);
		_stopwords.insert(s);
	}
}

bool Cppjieba::isStopWord(string & data)
{
	if(data == "\n")
	{
		return true;
	}
	set<string>::iterator it;
	it = find(_stopwords.begin(), _stopwords.end(), data);
	return it != _stopwords.end();
}

void Cppjieba::removeStopWords(vector<string> & words)
{
	function<bool(string &)> fun;
	fun = bind(&Cppjieba::isStopWord, this, std::placeholders::_1);
	words.erase(
				remove_if(words.begin(), words.end(), fun),
				words.end()
				);
}
#endif

}
