 ///
 /// @file    CppjiebaConf.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 09:53:29
 ///

#include "CppJieba/CppjiebaConf.h"

#include <stdlib.h>
#include <json/json.h>

#include <iostream>
#include <fstream>

namespace ccx{

using std::ifstream;
using std::cout;
using std::endl;

CppjiebaConf::CppjiebaConf()
{
	getConf();
}

const char * CppjiebaConf::get_DICT_PATH()
{
	return _dict_path.c_str();
}

const char * CppjiebaConf::get_HMM_PATH()
{
	return _hmm_path.c_str();
}

const char * CppjiebaConf::get_USER_DICT_PATH()
{
	return _user_dict_path.c_str();
}

const char * CppjiebaConf::get_IDF_PATH()
{
	return _idf_path.c_str();
}

const char * CppjiebaConf::get_STOP_WORD_PATH()
{
	return _stop_word_path.c_str();
}

void CppjiebaConf::getConf()
{
	ifstream ifs;
	ifs.open("../conf/Cppjieba/Cppjieba.json");
	if(!ifs.good())
	{
		cout << "Jieba open conf error" << endl;
		exit(EXIT_FAILURE);
	}
	Json::Reader reader;
	Json::Value root;
	if(!reader.parse(ifs, root, false))
	{
		cout << "Json error" << endl;
		exit(EXIT_FAILURE);
	}
	_dict_path = root["DICT_PATH"].asString();
	_hmm_path = root["HMM_PATH"].asString();
	_user_dict_path = root["USER_DICT_PATH"].asString();
	_idf_path = root["IDF_PATH"].asString();
	_stop_word_path = root["STOP_WORD_PATH"].asString();
}

}
