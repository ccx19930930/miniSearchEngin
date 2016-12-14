 ///
 /// @file    Eventfd.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-23 17:11:42
 ///

#include "tcp/Eventfd.h"

#include <sys/eventfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace ccx{

Eventfd::Eventfd()
: _eventfd(eventfd(0, 0))
{
}

void Eventfd::write(uint64_t & data)
{
	int ret;
	ret = ::write(_eventfd, &data, sizeof(uint64_t));
	if(8 != ret)
	{
		perror("write to eventfd error");
		exit(EXIT_FAILURE);	
	}
}

uint64_t Eventfd::read()
{
	int ret;
	uint64_t data;
	ret = ::read(_eventfd, &data, sizeof(uint64_t));
	if(8 != ret)
	{
		perror("read from eventfd error");
		exit(EXIT_FAILURE);	
	}
	return data;
}

int Eventfd::getEventfd()
{
	return _eventfd;
}

}
