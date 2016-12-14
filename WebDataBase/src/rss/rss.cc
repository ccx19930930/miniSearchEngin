///
/// @file    rss.cc
/// @author  chinxi(chenchengxi993@gmail.com)
/// @date    2016-10-27 17:27:49
///

#include "rss/rss.h"
#include "rss/tinyxml2.h"
#include "rss/rssConf.h"
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>


namespace ccx{

using namespace tinyxml2;
using std::cout;
using std::endl;
using std::ofstream;

RssReader::RssReader(RssData & rssData, rssConf & conf)
: _rssData(rssData)
, _conf(conf)
{
}


void RssReader::parseRss(const char * dirname)
{
	DIR * dir;
	dir = opendir(dirname);
	if(NULL == dir)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	struct dirent * p_dir;
	XMLDocument doc;
	XMLElement * pNode;
	XMLElement * sub_pNode;
	const char * title;
	const char * link;
	const char * content;
	int docid = 1;
	while((p_dir = readdir(dir)))
	{
		string tmp("../data/rss/");
		tmp += p_dir->d_name;
		string filename = tmp;
		doc.LoadFile(tmp.c_str());


		pNode = doc.FirstChildElement("rss");
		if(pNode)
		{
			pNode = pNode->FirstChildElement("channel");
		}else{
			pNode = doc.FirstChildElement("channel");
		}
		if(pNode)
		{
			pNode = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
			
			while(pNode)
			{
				RssItem rss;
				rss.from = filename;
				sub_pNode = pNode->FirstChildElement("title");
				if(sub_pNode)
				{
					title = sub_pNode->GetText();
					if(title)
					{
						rss.title = title;
					}else{
						pNode = pNode->NextSiblingElement();
						continue;
					}
				}
				//			cout << "6" << endl;
				sub_pNode = pNode->FirstChildElement("link");
				if(sub_pNode)
				{
					link = sub_pNode->GetText();
					if(link)
					{
						rss.link = link;
					}else{
						pNode = pNode->NextSiblingElement();
						continue;
					}
				}
				//			cout << "7" << endl;
				bool has_content = false;
				sub_pNode = pNode->FirstChildElement("content:encoded");
				if(sub_pNode)
				{
					content = sub_pNode->GetText();
					if(content)
					{
						has_content = true;
					}
				}
				//			cout << "9" << endl;
				if(!has_content)
				{
					sub_pNode = pNode->FirstChildElement("content");
					if(sub_pNode)
					{
						content = sub_pNode->GetText();
						if(content)
						{
							has_content = true;
						}
					}
				}
				if(!has_content)
				{
					sub_pNode = pNode->FirstChildElement("description");
					if(sub_pNode)
					{
						content = sub_pNode->GetText();
						if(content)
						{
							has_content = true;
						}
					}
				}
				//			cout << "8" << endl;
				if(has_content)
				{
					rss.content = replace(content);
					rss.docid = docid;
					++docid;
					_rssData.items.push_back(rss);
				}
				pNode = pNode->NextSiblingElement();
			}
		}
	}
	closedir(dir);
}




#define _USE_BOOST_REGEX_
#define _DELETE_SPACE_LINE_

string RssReader::replace(const char * data)
{
#ifdef _USE_BOOST_REGEX_
	boost::regex vowel_re("<.*?>");
	string temp;
	temp = boost::regex_replace(string(data), vowel_re, "");
#ifdef _DELETE_SPACE_LINE_
	vowel_re.set_expression("^$\\n");
	temp = boost::regex_replace(temp, vowel_re, "");
#endif
	return temp;
#else
	return data;
#endif
}

void RssReader::parse()
{
	string xmlpath;
	xmlpath = _conf.getInputXmlPath();
	parseRss(xmlpath.c_str());
}



}
