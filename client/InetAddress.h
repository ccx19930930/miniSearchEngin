 ///
 /// @file    InetAddress.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 16:37:09
 ///



#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


namespace ccx{

class InetAddress
{
	public:
		InetAddress();
		InetAddress(char * IP, unsigned short port);
		struct sockaddr * getAddr();
		size_t getAddrSize();
	private:
		void setFamily();
		void setPort(unsigned short port);
		void setIP();
		void setIP(char * IP);
		struct sockaddr_in _addr;
};

}

#endif
