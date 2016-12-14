 ///
 /// @file    InetAddress.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 20:47:11
 ///


#include "tcp/InetAddress.h"

namespace ccx{

InetAddress::InetAddress(uint16_t port)
{
	setFamily();
	setPort(port);
	setIP();
}

InetAddress::InetAddress(const string & IP, uint16_t port)
{
	setFamily();
	setPort(port);
	setIP(IP.c_str());
}

InetAddress::InetAddress(struct sockaddr_in addr)
: _addr(addr)
{
}


void InetAddress::setFamily()
{
	_addr.sin_family = AF_INET;	
}

void InetAddress::setPort(uint16_t port)
{
	_addr.sin_port = htons(port);
}

void InetAddress::setIP()
{
	_addr.sin_addr.s_addr=INADDR_ANY;
}

void InetAddress::setIP(const char * IP)
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

uint16_t InetAddress::getPort()
{
	uint16_t port;
	port = ntohs(_addr.sin_port);
	return port;
}

string InetAddress::getIP()
{
	char * ip;
	ip = inet_ntoa(_addr.sin_addr);
	return string(ip);
}


}
