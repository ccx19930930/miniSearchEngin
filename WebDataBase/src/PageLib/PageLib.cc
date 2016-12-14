 ///
 /// @file    PageLib.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-29 11:23:07
 ///

#include "PageLib/PageLib.h"

#include <iostream>

namespace ccx{

using std::endl;
using std::cout;

PageLib::PageLib()
: _conf()
, _data()
, _output(_data, _conf)
, _rss(_data, _conf)
, _word(_data)
, _repet(_data)
, _inv(_data)
, _dictionary(_data)
{
}

void PageLib::makePagLib()
{
#if 1
	_rss.parse();
	_output.outputRssinitall();
	
	_word.do_Count();
	_repet.Repet();
	_inv.makeInvertindex();
	_dictionary.makeDictionary();

	_output.outputGroupmsg();
	_output.outputWordfrequency();
	_output.outputRipepage();
	_output.outputInvertindex();
#endif
#if 0
	_data._dictionary.leading_in();			
	_output.outputInvertindex();
#endif

}




}
