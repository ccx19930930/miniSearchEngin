 /// /// @file    RssOutput.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-27 21:47:49
 ///

#include "rss/rssConf.h"
#include "rss/RssOutput.h"
#include <stdlib.h>
#include <json/json.h>
#include <boost/regex.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

namespace ccx{

using std::ofstream;
using std::endl;
using std::cout;
using std::stringstream;

RssOutput::RssOutput(RssData & data, rssConf & conf)
: _data(data)
, _conf(conf)
{
}


//XML格式输出
int RssOutput::outputRss(ofstream & ofs, RssItemIt & it)
{
	stringstream ss;
	ss << "<doc>" << "from:" << it->from << endl;
	ss << "\t<docid>" << it->docid << "</docid>" << endl;
	ss << "\t<title>" << it->title << "</title>" << endl;	
	ss << "\t<link>" << it->link << "</link>" << endl;	
	ss << "\t<content>" << it->content << "</content>" << endl;	
	ss << "</doc>" << endl;
	string s;
	int size = 0;	

	while(1)
	{
		if(!ss.good())
		{
			break;
		}
		getline(ss, s);
		size += s.size();
		ofs << s << endl;
	}
	return size;
}

void RssOutput::outputRssinitall()
{
	string path;
	path = _conf.getOutputRssinitailPath();
	ofstream ofs(path.c_str(),std::ios::app);

	if(!ofs.good())
	{
		cout << "open file rssinitail.lib error" << endl;
		exit(EXIT_FAILURE);
	}
	RssItemIt it_rss;	
	
	it_rss = _data.items.begin();
	
	for(; it_rss != _data.items.end(); ++it_rss)
	{
		outputRss(ofs, it_rss);
	}
}	

void RssOutput::outputRipepage()
{
	string path;
	path = _conf.getOutputRipepagePath();
	ofstream ofs_page(path.c_str(),std::ios::app);
	if(!ofs_page.good())
	{
		cout << "open file Ripepage.lib error" << endl;
		exit(EXIT_FAILURE);
	}

	Json::Value root;
	Json::FastWriter writer;
	Json::Value person;

	int offset = 0;
	int length = 0;

	GroupIt it_group;
	it_group = _data._group.begin();
	for(; it_group != _data._group.end(); ++it_group)
	{
		list<RssItemIt>::iterator it_list;	
		it_list = it_group->second.begin();
		for(; it_list != it_group->second.end(); ++it_list)
		{
			RssItemIt it_rss;
			it_rss = *it_list;
			length = outputRss(ofs_page, it_rss);
			
			person["docid"] = it_rss->docid;
			person["offset"] = offset;
			person["length"] = length;
			root.append(person);
			offset += length;
		}
	}

	path = _conf.getOutputOffsetPath();
	ofstream ofs_offset(path.c_str(),std::ios::app);
	if(!ofs_offset.good())
	{
		cout << "open file offset.lib error" << endl;
		exit(EXIT_FAILURE);
	}
	
	ofs_offset << "[" << endl;
	int size = root.size();
	for(int i = 0; i < size; ++i)
	{
		string json_file = writer.write(root[i]);
		int len = json_file.size();
		json_file[len - 1] = ' ';
		ofs_offset << "\t" << json_file;
		if(i != size -1)
		{
			ofs_offset << "," << endl;
		}
	}
	ofs_offset << endl << "]" << endl;
	ofs_offset.close();
}


//词频输出
void RssOutput::outputWord(ofstream & ofs, RssItemIt & it)
{
	ofs << "title : " << it->title << endl;
	int sum = 0;
	WordSortedIt it_word;
	it_word = it->wordmsg.begin();
	for(; it_word != it->wordmsg.end(); ++it_word)
	{
		ofs << "|+|" << it_word->word << "|+| : " << it_word->freq;
		++sum;
	}
	ofs << " -------> " << sum << endl;
}


void RssOutput::outputWordfrequency()
{
	string path;
	path = _conf.getOutputWordfrequencyPath();
	ofstream ofs(path.c_str(),std::ios::app);
	if(!ofs.good())
	{
		cout << "open file wordfrequency.lib error" << endl;
		exit(EXIT_FAILURE);
	}

	vector<RssItem>::iterator it_rss;
	it_rss = _data.items.begin();
	for(; it_rss != _data.items.end(); ++it_rss)
	{
		if(it_rss->wordmsg.size())
		  outputWord(ofs, it_rss);
	}
	ofs.close();
}


void RssOutput::outputGroupmsg()
{
	string path;
	path = _conf.getOutputGroupmsgPath();
	ofstream ofs(path.c_str(),std::ios::app);
	if(!ofs.good())
	{
		cout << "open file group.lib error" << endl;
		exit(EXIT_FAILURE);
	}

	GroupIt it_group;
	it_group = _data._group.begin();
	int i = 1;	
	for(; it_group != _data._group.end(); ++it_group, ++i)
	{
		ofs << "Group " << i << " : " << it_group->first << endl;
		list<RssItemIt>::iterator it_list;	
		it_list = it_group->second.begin();
		for(; it_list != it_group->second.end(); ++it_list)
		{
			RssItemIt it_rss;
			it_rss = *it_list;
			outputWord(ofs, it_rss);
		}
	}
	ofs.close();
}


void RssOutput::outputInvertindex()
{
	_data._dictionary.leading_out();
}
#if 0
{
	Json::Value root;
	Json::FastWriter writer;
	Json::Value person;
	

	FreqIt it_inv;

	it_inv = _data._freqs.begin();

	for(; it_inv != _data._freqs.end(); ++it_inv)
	{
		Json::Value elems;
		person["word"] = it_inv->first;
		vector<Invertindex>::iterator it_vec;
		it_vec = it_inv->second.begin();
		for(; it_vec != it_inv->second.end(); ++it_vec)
		{
			Json::Value elem;
			elem["docid"] = it_vec->docid;
			elem["freq"] = it_vec->freq;
			elem["weight"] = it_vec->weight;

			elems.append(elem);
		}
		person["elem"] = elems;
		root.append(person);
	}

	ofstream ofs;
	ofs.open(_conf.getOutputInvertindexPath());
	if(!ofs.good())
	{
		cout << "open file group.lib error" << endl;
		exit(EXIT_FAILURE);
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
#endif

}
