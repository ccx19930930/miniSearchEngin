 ///
 /// @file    TcpServer.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-22 14:21:04
 ///

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"
#include "TcpConnect.h"
#include "EpollPoller.h"
#include "root/Noncopyable.h"

namespace ccx{

typedef EpollPoller::ConnectCallback TcpServerCallback;

class TcpServer
: private Noncopyable
{
	public:
		TcpServer(const string & IP, uint16_t port);
		~TcpServer();
		void start();
		void stop();
	public:
		void setConnectionCallback(TcpServerCallback cb);
		void setMessageCallback(TcpServerCallback cb);
		void setCloseCallback(TcpServerCallback cb);
	private:
		Socket _socket;
		InetAddress _addr;
		EpollPoller _epoll;
		bool _isstart;
};

}

#endif
