 ///
 /// @file    Eventfd.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-23 17:06:49
 ///

#ifndef __EVENTFD_H__
#define __EVENTFD_H__


#include <sys/eventfd.h>

namespace ccx{

class Eventfd
{
	public:
		Eventfd();
		void write(uint64_t & data);
		uint64_t read();
		int getEventfd();
	private:
		int _eventfd;
};

}

#endif
