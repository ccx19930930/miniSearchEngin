 ///
 /// @file    Cppjieba.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 10:11:56
 ///

#ifndef __CPPJIEBA_H__
#define __CPPJIEBA_H__

#include "cppjieba/Jieba.hpp"
#include "CppjiebaConf.h"

#include <vector>
#include <set>

namespace ccx{

#define NEED_REMOVE_STOP

using std::set;
using std::vector;

class Cppjieba
{
	public:
		Cppjieba();
	public:
//		vector<string>::iterator getWord();
//		ssize_t getWordSize();

		vector<cppjieba::Word>::iterator getJiebaWord();
		ssize_t getJiebaWordSize();
	public:
		void Cut_With_Hmm(const string & data, vector<string> & words);
		void Cut_Without_Hmm(const string & data, vector<string> & words);
		void Cut_All(const string & data, vector<string> & words);
		void Cut_For_Search(const string & data, vector<string> & words);	
		void Insert_User_Word(const string & data);
		void Cut_For_Search_Word_With_Offset(const string & data);
		void Lookup_Tag_For_Single_Token();
		void Tagging();
		void Keyword_Extraction();
	private:
		CppjiebaConf _conf;
		cppjieba::Jieba _jieba;
	private:
		vector<cppjieba::Word> _jiebawords;
		set<string> _stopwords;
#ifdef NEED_REMOVE_STOP
	private:
		void getStopWords();
		bool isStopWord(string & data);
		void removeStopWords(vector<string> & words);
#endif

};


}

#endif
