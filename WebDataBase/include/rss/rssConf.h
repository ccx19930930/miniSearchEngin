 ///
 /// @file    rssConf.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-28 11:40:32
 ///


#ifndef __RSSCONF_H__
#define __RSSCONF_H__

#include <string>


namespace ccx{

using std::string;

class rssConf
{
	public:
		rssConf();


	private:
		void getConf();

//需要的路径
	public:
		string getInputXmlPath();
		string getOutputRipepagePath();
		string getOutputOffsetPath();
		string getOutputInvertindexPath();
	private:
		string _intputXmlPath;
		string _outputRipepagePath;
		string _outputOffsetPath;
		string _outputInvertindexPath;
//测试使用的路径
	public:
		string getOutputRssinitailPath();
		string getOutputWordfrequencyPath();
		string getOutputGroupmsgPath();
	private:
		string _outputRssinitailPath;
		string _outputWordfrequencyPath;
		string _outputGroupmsgPath;
};



}

#endif
