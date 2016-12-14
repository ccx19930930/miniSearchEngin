 ///
 /// @file    Cahce.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 23:49:45
 ///

#include "Cache/Cache.h"
#include "thread_pool/safeMutex.h"
#include <json/json.h>

#include <fstream>
#include <iostream>

namespace ccx{

using std::pair;
using std::endl;
using std::cout;
using std::ofstream;
using std::ifstream;

typedef unordered_map<string, CacheElem>::iterator UmapIt;

Cache::Cache(int num)
: _conf()
, _rootdata(new CacheData)
, _mutex()
, _cond(_mutex)
, _isBackup(false)
{
	for(int i = 0; i < num; ++i)
	{
		pCacheData ptemp(new CacheData);
		_subDataVec.push_back(ptemp);	
		_subDataList.push_back(ptemp);
	}
	ReadFromFile();
}

void Cache::WriteInto(pCacheData & lhs, pCacheData & rhs)
{
	UmapIt it_lhs;
	it_lhs = lhs->_cache.begin();
	for(; it_lhs != lhs->_cache.end(); ++it_lhs)
	{
		UmapIt it_rhs;
		it_rhs = rhs->_cache.find(it_lhs->first);
		if(it_rhs == rhs->_cache.end())
		{
			pair<string, CacheElem> temp;
			temp.first = it_lhs->first;
			temp.second = it_lhs->second;
			rhs->_cache.insert(temp);
		}else{
			it_rhs->second._visit_num += it_lhs->second._visit_num;
		}
	}
}

void Cache::Backup()	
{
	_rootdata->_cache.clear();
	vector<pCacheData>::iterator it_vec;
	it_vec = _subDataVec.begin();
	for(; it_vec != _subDataVec.end(); ++it_vec)
	{
		WriteInto(*it_vec, _rootdata);
	}
	safeMutex mutex(_mutex);
	_isBackup = true;
}

void Cache::CanWriteBack()
{
	safeMutex mutex(_mutex);
	while(_subDataList.size() != _subDataVec.size())
	{
		_cond.wait();
	}
}

void Cache::WriteToFile()
{
	Json::Value root;
	Json::FastWriter writer;

	UmapIt it_map;

	it_map = _rootdata->_cache.begin();
	for(; it_map != _rootdata->_cache.end(); ++it_map)
	{
		Json::Value elem;
		elem["key"] = it_map->first;
		elem["visit_num"] = it_map->second._visit_num;	
		elem["data"] = it_map->second._data;
		
		root.append(elem);
	}

	ofstream ofs;
	const char * path = _conf.getCachePath().c_str();
	ofs.open(path);
	if(!ofs.good())
	{
		cout << "open " << path << " error" << endl;
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

void Cache::WriteBack()
{
	CanWriteBack();	
	vector<pCacheData>::iterator it_vec;
	it_vec = _subDataVec.begin();
	for(; it_vec != _subDataVec.end(); ++it_vec)
	{
		(*it_vec)->_cache.clear();
		WriteInto(_rootdata, *it_vec);
	}
	safeMutex mutex(_mutex);
	_isBackup = false;
}

void Cache::push(pCacheData ptemp)
{
	_subDataList.push_back(ptemp);
	safeMutex mutex(_mutex);
	if(_isBackup)
	{
		_cond.notify();
	}
}

Cache::pCacheData Cache::pop()
{
	safeMutex mutex(_mutex);
	if(_isBackup)
	{
		return NULL;
	}
	pCacheData temp = _subDataList.front();
	_subDataList.pop_front();
	return temp;	
}

bool Cache::Query(string & data, const string & words)
{
	cout << "find : " << words << endl;
	pCacheData pcache;
	pcache = pop();
	if(!pcache)
	{
		pcache = _rootdata;
	}
	
	UmapIt it_map;
	it_map = pcache->_cache.find(words);
	if(it_map == pcache->_cache.end())
	{
		if(pcache != _rootdata)
		{
			push(pcache);
		}
		return false;
	}
	
	data = it_map->second._data;
	if(pcache != _rootdata)
	{
		++(it_map->second._visit_num);
		push(pcache);
	}
	//cout << "data : " << data << endl;
	return true;	
}

void Cache::pushData(pair<string, CacheElem> & data)
{
	pCacheData pcache;
	pcache = pop();
	if(pcache)
	{
		UmapIt it_map;
		it_map = pcache->_cache.find(data.first);
		if(it_map == pcache->_cache.end())
		{
			pcache->_cache.insert(data);
		}else{
			++(it_map->second._visit_num);
		}
		push(pcache);
	}
}

void Cache::synchronization()
{
	Backup();
	WriteBack();
	WriteToFile();
}

void Cache::ReadFromFile()
{
	ifstream ifs;
	const char * path = _conf.getCachePath().c_str();
	ifs.open(path);
	if(!ifs.good())
	{
		cout << "open " << _conf.getCachePath() << " error" << endl;
	}else{
	
	Json::Value root;
	Json::Reader reader;
	
	if(!reader.parse(ifs, root, false))
	{
		cout << "Cache read from file error " << endl;
		exit(EXIT_FAILURE);
	}
	
	int size = root.size();

	for(int i = 0; i < size; ++i)
	{
		pair<string, CacheElem> elem;
		elem.first = root[i]["key"].asString();
		elem.second._visit_num = root[i]["visit_num"].asInt();
		elem.second._data = root[i]["data"].asString();
		_rootdata->_cache.insert(elem);
	}
	WriteBack();
	cout << "Cache Ready!" << endl;
	}
}

}
