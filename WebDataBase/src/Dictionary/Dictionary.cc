 ///
 /// @file    Dictionary.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-03 10:47:12
 ///

#include "Dictionary/Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>

namespace ccx{

using std::endl;
using std::cout;
using std::pair;
using std::ofstream;
using std::ifstream;

Dictionary::Dictionary()
: _dictionary(new DictElem)
, _conf()
{
	_dictionary->_Freq = 0;
	_pcur = _dictionary;
}

void Dictionary::splitWord(const string & word, vector<string> & characters)
{
	int num = word.size();
	int i = 0;
	while(i < num)
	{
		int size = 1;
		if(word[i] & 0x80)
		{
			char temp = word[i];
			temp <<= 1;
			do{
				temp <<= 1;
				++size;
			}while(temp & 0x80);
		}
		string subWord;
		subWord = word.substr(i, size);
		characters.push_back(subWord);
		i += size;
	}
}

void Dictionary::AddWord(const string & word, WordMsg & msg)
{
	//cout << msg._freq << "===" << msg._weight << endl;
	vector<string> characters;
	splitWord(word, characters);
	
	vector<string>::iterator it_char;
	it_char = characters.begin();	
	pDictElem root;
	root = _dictionary;
	for(; it_char != characters.end(); ++it_char)
	{
		WordIt it_word;
		it_word = root->_words.find(*it_char);
		
		if(it_word == root->_words.end())
		{
			pair<string, pDictElem> temp;
			temp.first = *it_char;
			pDictElem dictemp(new DictElem);
			dictemp->_word = *it_char;
			dictemp->_Freq = 0;
			temp.second = dictemp;
			root->_words.insert(temp);
			root = dictemp;
		}else{
			root = it_word->second;
		}
	}
	++(root->_Freq);
	root->_msg.push_back(msg);
}

void Dictionary::push(const string & word, WordMsg & msg)
{
	AddWord(word, msg);
}

void Dictionary::push(map<string, WordMsg> & words)
{ 
	map<string, WordMsg>::iterator it;
	it = words.begin();
	for(; it != words.end(); ++it)
	{
		AddWord(it->first, it->second);
	}
}

int Dictionary::search(const string & word, vector<WordMsg> & msg)
{
	pDictElem root = _dictionary;
	vector<string> temp;
	splitWord(word, temp);

	int ret = search(temp, root);
	int size = temp.size();
	if(ret != size)
	{
		return -1;
	}
	for(auto & elem : root->_msg)
	{
		msg.push_back(elem);
	}
	return root->_Freq;
}

int Dictionary::search(vector<string> & characters, pDictElem & root)
{
	vector<string>::iterator it_char;
	it_char = characters.begin();	
	root = _dictionary;
	int i = 0;
	for(; it_char != characters.end(); ++it_char, ++i)
	{
		WordIt it_word;
		it_word = root->_words.find(*it_char);

		if(it_word == root->_words.end())
		{
			break;
		}else{
			root = it_word->second;
		}
	}
	return i;
}

bool Dictionary::associate(const string & word, vector<string> & data)
{
	pDictElem root = _dictionary;
	vector<string> temp;
	splitWord(word, temp);

	int ret = search(temp, root);
	int size = temp.size();
	if(ret != size)
	{
		return false;
	}

	list<WordIt> stackWord;
	list<pDictElem> stackDict;
	next(root, stackWord, stackDict);
	while(root)
	{
		string temp = getCurWord(stackWord);
		data.push_back(temp);	
		next(root, stackWord, stackDict);
	}

	if(!data.size())
	{
		return false;
	}
	return true;
}

//遍历用

void Dictionary::resetPoint(pDictElem pcur)
{
	_pcur = pcur;
	if(_stackDict.size())
	{
		_stackDict.clear();
	}
	if(_stackWord.size())
	{
		_stackWord.clear();
	}
	next();
}

void Dictionary::resetIt()
{
	resetPoint(_dictionary);
}

void Dictionary::next()
{
	next(_pcur, _stackWord, _stackDict);
}

void Dictionary::next(pDictElem & pcur, list<WordIt> & stackWord, list<pDictElem> & stackDict)
{
	while(pcur)
	{
		nextWord(pcur, stackWord, stackDict);
		if(!pcur || pcur->_Freq)
		{
			break;
		}
	}
}

void Dictionary::nextWord(pDictElem & pcur, list<WordIt> & stackWord, list<pDictElem> & stackDict)
{
	if(pcur)
	{
		if(pcur->_words.size())
		{
			stackDict.push_back(pcur);
			stackWord.push_back(pcur->_words.begin());
			pcur = stackWord.back()->second;
		}else{
			++(stackWord.back());
		}
		while(stackWord.back() == stackDict.back()->_words.end())
		{
			stackDict.pop_back();
			stackWord.pop_back();
			if(!stackDict.size())
			{
				pcur = NULL;
			}
			++(stackWord.back());
		}
		if(pcur)
		{
			pcur = stackWord.back()->second;
		}	
	}
}

string Dictionary::getCurChar()
{
	return _pcur->_word;
}

int Dictionary::getCurWordFreq()
{
	return _pcur->_Freq;
}

string Dictionary::getCurWord()
{
	return getCurWord(_stackWord);
}

string Dictionary::getCurWord(list<WordIt> & stackWord)
{
	string temp;
	list<WordIt>::iterator it_word;	
	it_word = stackWord.begin();	

	for(; it_word != stackWord.end(); ++it_word)
	{
		temp += (*it_word)->first;
	}
	return temp;
}

bool Dictionary::isEnd()
{
	return _pcur == NULL;
}

void Dictionary::leading_in()//导入，失败没必要退出程序
{
	ifstream ifs;
	const char * path = _conf.getDictionaryPath().c_str();
	ifs.open(path);
	if(!ifs.good())
	{
		cout << "open Dictionary.json error(leading_in)" << endl;
	}else{
		Json::Value root;
		Json::Reader reader;

		if(!reader.parse(ifs, root, false))
		{
			cout << "json read Dictionary.json error" << endl;
		}else{
			int size = root.size();
			for(int i = 0; i < size; ++i)
			{
				string word = root[i]["Word"].asString();
				int subsize = root[i]["Msg"].size();
				for(int j = 0; j < subsize; ++j)
				{
					WordMsg msg;
					msg._docid = root[i]["Msg"][j]["Docid"].asInt();
					msg._freq = root[i]["Msg"][j]["Freq"].asInt();
					msg._weight = root[i]["Msg"][j]["Weight"].asDouble();
					AddWord(word, msg);
				}
			}
		}
	}
}

void Dictionary::leading_out()
{
	Json::Value root;
	Json::FastWriter writer;

	resetIt();

	while(!isEnd())
	{
		Json::Value elem;
		elem["Word"] = getCurWord();
		Json::Value msg;	

		for(auto & elem : _pcur->_msg)
		{
			Json::Value temp;
			temp["Docid"] = elem._docid;
			temp["Freq"] = elem._freq;
			temp["Weight"] = elem._weight;
			msg.append(temp);
		}
		elem["Msg"] = msg;
		root.append(elem);
		next();
	}

	ofstream ofs;
	const char * path = _conf.getDictionaryPath().c_str();
	ofs.open(path);
	if(!ofs.good())
	{
		cout << "open Dictionary.json error(leading_out)" << endl;
		ofs.open("Dictionary.tmp");
		if(!ofs.good())
		{
			exit(EXIT_FAILURE);
		}
	}
	ofs << "[" << endl;
	int size = root.size();
	for(int i = 0; i < size; ++i)
	{
		string json_file = writer.write(root[i]);
		int len = json_file.size();
		json_file[len - 1] = ' ';
		ofs << "\t" << json_file;
		if(i != size -1)
		{
			ofs << "," << endl;
		}
	}
	ofs << endl << "]" << endl;
	ofs.close();

}

}
