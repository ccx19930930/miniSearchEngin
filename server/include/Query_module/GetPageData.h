 ///
 /// @file    GetPageData.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 16:30:26
 ///

#ifndef __GETPAGEDATA_H__
#define __GETPAGEDATA_H__

#include "root/Noncopyable.h"
#include "Query_module/PageData.h"

namespace ccx{


class PageConf;
class GetPageData
: private Noncopyable
{
	public:
		GetPageData(PageData & data, PageConf & _conf);

		void getPageData();

	private:
		void getRssItem();
		void getOffset();
		void getInvertindex();
	private:
		PageData & _data;
		PageConf & _conf;
};


}
#endif
