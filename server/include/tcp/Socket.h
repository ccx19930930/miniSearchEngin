 ///
 /// @file    Socket.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 16:15:41
 ///



#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "InetAddress.h"
#include "root/Noncopyable.h"

namespace ccx{


enum SOCK
{
	LOCAL,
	PEER
};


class Socket
: private Noncopyable
{
	public:
		Socket();
		Socket(int fd);
		void ready(InetAddress & addr);
		int socketAccess();
		int getSocket();
		struct sockaddr_in getLocalAddr();
		struct sockaddr_in getPeerAddr();
		void shutdownWrite();
	private:
		void setReuseAddr(bool on);
		void setReusePort(bool on);
		void setKeepAlive(bool on);
		void setTcpNoDelay(bool on);
		void bindAddress(InetAddress & addr);
		void socket_listen(int num);
		int _sfd;
};

}


#endif
