 ///
 /// @file    Cache.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-12-01 23:47:16
 ///


#ifndef __CACHE_H__
#define __CACHE_H__

#include "CacheData.h"
#include "CacheConf.h"

#include "thread_pool/Mutex.h"
#include "thread_pool/Cond.h"

#include <list>
#include <memory>
#include <vector>

namespace ccx{

using std::list;
using std::shared_ptr;
using std::vector;
using std::pair;

class Cache
{
	public:
		Cache(int num);
	public:
		typedef shared_ptr<CacheData> pCacheData;
		bool Query(string & data, const string & words);
		void pushData(pair<string, CacheElem> & data);


		void push(pCacheData ptemp);
		pCacheData pop();
		void CanWriteBack();
		void WriteInto(pCacheData & lhs, pCacheData & rhs);
	private:
		CacheConf _conf;
		pCacheData _rootdata;
		vector<pCacheData> _subDataVec;
		list<pCacheData> _subDataList; 
		Mutex _mutex;
		Cond _cond;
		bool _isBackup;
//同步	
	public:
		void synchronization();
	private:
		void ReadFromFile();
		void Backup();
		void WriteBack();
		void WriteToFile();
};






}


#endif
