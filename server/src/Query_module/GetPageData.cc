 ///
 /// @file    GetPageData.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 16:33:29
 ///


#include "Query_module/GetPageData.h"
#include "Query_module/PageConf.h"
#include "Query_module/tinyxml2.h"


#include <stdlib.h>
#include <json/json.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace ccx{

using namespace tinyxml2;
using std::ifstream;
using std::cout;
using std::endl;
using std::pair;
using std::stringstream;

GetPageData::GetPageData(PageData & data, PageConf & conf)
: _data(data)
, _conf(conf)
{
}

void GetPageData::getPageData()
{
	getRssItem();
	getOffset();
	getInvertindex();
}

void GetPageData::getRssItem()
{
	
	XMLDocument doc;
	XMLElement * pNode;
	XMLElement * sub_pNode;
	const char * docid;
	const char * title;
	const char * link;
	const char * content;


	doc.LoadFile(_conf.getRipepagePath().c_str());

	pNode = doc.FirstChildElement("doc");
	
	while(pNode)
	{
		RssItem item;	
		sub_pNode = pNode->FirstChildElement("docid");
		docid = sub_pNode->GetText();
		item.docid = ::atoi(docid);

		sub_pNode = pNode->FirstChildElement("title");
		title = sub_pNode->GetText();
		item.title = title;

		sub_pNode = pNode->FirstChildElement("link");
		link = sub_pNode->GetText();
		item.link = link;
		
		sub_pNode = pNode->FirstChildElement("content");
		stringstream ss;	
		content = sub_pNode->GetText();
		
		ss << content;
		while(1)
		{
			if(!ss.good())
			{
				break;
			}
			string s;
			getline(ss, s);
			item.content.push_back(s);
		}
		_data._items.push_back(item);

		pNode = pNode->NextSiblingElement();
	}
}

void GetPageData::getOffset()
{
	ifstream ifs;
	ifs.open(_conf.getOffsetPath());
	if(!ifs.good())
	{
		cout << "open offset error" << endl;
		exit(EXIT_FAILURE);	
	}

	Json::Value root;
	Json::Reader reader;

	if(!reader.parse(ifs, root, false))
	{
		cout << "json reader parse error" << endl;
		exit(EXIT_FAILURE);
	}

	int size;
	size = root.size();

	for(int i = 0; i < size; ++i)
	{
		Offset offset;
		offset.docid = root[i]["docid"].asInt();	
		offset.offset = root[i]["offset"].asInt();
		offset.length = root[i]["length"].asInt();
		_data._offset.push_back(offset);
	}
	ifs.close();
}

void GetPageData::getInvertindex()
{
	_data._dictionary.leading_in();
#if 0
	ifstream ifs;
	ifs.open(_conf.getInvertindexPath());
	if(!ifs.good())
	{
		cout << "open Invertindex error" << endl;
		exit(EXIT_FAILURE);	
	}

	Json::Value root;
	Json::Reader reader;
	if(!reader.parse(ifs, root, false))
	{
		cout << "json reader parse error" << endl;
		exit(EXIT_FAILURE);
	}

	int size;
	size = root.size();

	for(int i = 0; i < size; ++i)
	{
		pair<string, vector<Invertindex> > inv;
		inv.first = root[i]["word"].asString();

		int num;
		num = root[i]["elem"].size();

		double weight = 0.0;
		for(int j = 0; j < num; ++j)
		{
			Invertindex invElem;

			invElem.docid = root[i]["elem"][j]["docid"].asInt();
			invElem.freq = root[i]["elem"][j]["freq"].asInt(); 
			invElem.weight = root[i]["elem"][j]["weight"].asDouble(); 
			inv.second.push_back(invElem);

			weight += (invElem.weight * invElem.weight);
		}
		Invertindex base;
		base.docid = 0;
		base.freq = 0;
		base.weight = sqrt(weight);//最后一项存base相关

		inv.second.push_back(base);

		_data._invertindex.insert(inv);
	}
	ifs.close();
#endif
}


}
