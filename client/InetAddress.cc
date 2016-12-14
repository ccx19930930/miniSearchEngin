 ///
 /// @file    InetAddress.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 20:47:11
 ///


#include "InetAddress.h"

namespace ccx{

InetAddress::InetAddress()
{
	setFamily();
	setPort(2000);
	setIP();
}

InetAddress::InetAddress(char * IP, unsigned short port)
{
	setFamily();
	setPort(port);
	setIP(IP);
}



void InetAddress::setFamily()
{
	_addr.sin_family = AF_INET;	
}

void InetAddress::setPort(unsigned short port)
{
	_addr.sin_port = htons(port);
}

void InetAddress::setIP()
{
	_addr.sin_addr.s_addr=INADDR_ANY;
}

void InetAddress::setIP(char * IP)
{
	_addr.sin_addr.s_addr = ::inet_addr(IP);
}

struct sockaddr * InetAddress::getAddr()
{
	return (struct sockaddr*)&_addr;
}

size_t InetAddress::getAddrSize()
{
	return sizeof(struct sockaddr);
}

}
