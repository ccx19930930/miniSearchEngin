 ///
 /// @file    InetAddress.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 16:37:09
 ///



#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include "root/Noncopyable.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

namespace ccx{

using std::string;

class InetAddress
{
	public:
		InetAddress(uint16_t port);
		InetAddress(const string & IP, uint16_t port);
		InetAddress(struct sockaddr_in addr);
		struct sockaddr * getAddr();
		size_t getAddrSize();
		uint16_t getPort();
		string getIP();
	private:
		void setFamily();
		void setPort(uint16_t port);
		void setIP();
		void setIP(const char * IP);
		struct sockaddr_in _addr;
};

}

#endif
