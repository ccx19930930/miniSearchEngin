 ///
 /// @file    CppjiebaConf.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-25 09:37:08
 ///


#ifndef __CPPJIEBACONF_H__
#define __CPPJIEBACONF_H__

#include "cppjieba/Jieba.hpp"

#include <string>
#include <vector>

namespace ccx{

using std::string;
using std::vector;

class CppjiebaConf
{
	public:
		CppjiebaConf();
	public:
		const char * get_DICT_PATH();
		const char * get_HMM_PATH();
		const char * get_USER_DICT_PATH();
		const char * get_IDF_PATH();
		const char * get_STOP_WORD_PATH();
	private:
		void getConf();
		string _dict_path;
		string _hmm_path;
		string _user_dict_path;
		string _idf_path;
		string _stop_word_path;
};

}

#endif
