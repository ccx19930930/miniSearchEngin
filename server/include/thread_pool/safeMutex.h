 ///
 /// @file    safeMutex.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 20:54:53
 ///


#ifndef __SAFEMUTEX_H__
#define __SAFEMUTEX_H__

#include "Mutex.h"


namespace ccx{

class safeMutex
{
	public:
		safeMutex(Mutex & mutex);
		~safeMutex();
	private:
		Mutex & _mutex;
};


}

#endif
