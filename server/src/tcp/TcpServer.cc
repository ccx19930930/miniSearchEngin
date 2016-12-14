 ///
 /// @file    TcpServer.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-22 14:28:47
 ///

#include "tcp/TcpServer.h"

#include <iostream>


namespace ccx{

using std::cout;
using std::endl;

TcpServer::TcpServer(const string & IP, uint16_t port)
: _socket()
, _addr(IP, port)
, _epoll(_socket)
, _isstart(false)
{
	_socket.ready(_addr);
	cout << "IP : " << _addr.getIP()
		<< "\tport : " << _addr.getPort()
		<< endl;
}

TcpServer::~TcpServer()
{
	if(_isstart)
	{
		stop();
	}
}


void TcpServer::start()
{
	_isstart = true;
	_epoll.loop();
}


void TcpServer::stop()
{
	_epoll.unloop();
	_isstart = false;
}


void TcpServer::setConnectionCallback(TcpServerCallback cb)
{
	_epoll.setConnectionCallback(cb);
}

void TcpServer::setMessageCallback(TcpServerCallback cb)
{
	_epoll.setMessageCallback(cb);
}

void TcpServer::setCloseCallback(TcpServerCallback cb)
{
	_epoll.setCloseCallback(cb);
}


}
