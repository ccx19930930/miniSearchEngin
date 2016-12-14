 ///
 /// @file    Socket.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 20:29:43
 ///


#include "tcp/Socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

#include <iostream>

namespace ccx{

using std::endl;
using std::cout;

Socket::Socket()
: _sfd(::socket(AF_INET, SOCK_STREAM, 0))
{
	if(-1 == _sfd)
	{
		perror("create socket error");
		exit(EXIT_FAILURE);
	}
}

Socket::Socket(int fd)
: _sfd(fd)
{
}



void Socket::bindAddress(InetAddress & addr)
{
	int ret;
	ret = ::bind(_sfd, addr.getAddr(), addr.getAddrSize());
	if(-1 == ret)
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}
}

void Socket::socket_listen(int num)
{
	int ret;
	ret = ::listen(_sfd, num);
	if(-1 == ret)
	{
		perror("listen error");
		exit(EXIT_FAILURE);
	}
}


int Socket::socketAccess()
{
	int new_fd = ::accept(_sfd, NULL, NULL);
	if(-1 == new_fd)
	{
		perror("accept error");
		exit(EXIT_FAILURE);
	}
	return new_fd;
}

void Socket::setReuseAddr(bool on)
{
	int optval = on ? 1 : 0;
	int ret;
	ret = ::setsockopt(_sfd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
	if(-1 == ret)
	{
		perror("setReuseAddr error");
		exit(EXIT_FAILURE);
	}
}
void Socket::setReusePort(bool on)
{
	int optval = on ? 1 : 0;
	int ret;
	ret = ::setsockopt(_sfd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof optval));
	if(-1 == ret)
	{
		perror("setReusePort error");
		exit(EXIT_FAILURE);
	}
}
void Socket::setKeepAlive(bool on)
{
	int optval = on ? 1 : 0;
	int ret;
	ret = ::setsockopt(_sfd, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof optval));
	if(-1 == ret)
	{
		perror("setKeepAlive error");
		exit(EXIT_FAILURE);
	}
}
void Socket::setTcpNoDelay(bool on)
{
	int optval = on ? 1 : 0;
	int ret;
	ret = ::setsockopt(_sfd, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof optval));
	if(-1 == ret)
	{
		perror("setTcpNoDelay error");
		exit(EXIT_FAILURE);
	}
}


void Socket::ready(InetAddress & addr)
{
	setReuseAddr(true);
	setReusePort(true);
	setKeepAlive(false);
	setTcpNoDelay(false);
	bindAddress(addr);
	socket_listen(10);




}

int Socket::getSocket()
{
	return _sfd;
}

struct sockaddr_in Socket::getLocalAddr()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int ret;
	ret = ::getsockname(_sfd, (struct sockaddr*)&addr, &len);
	if(-1 == ret)
	{
		perror("getsockname error");
		exit(EXIT_FAILURE);
	}
	return addr;
}

struct sockaddr_in Socket::getPeerAddr()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int ret;
	ret = ::getpeername(_sfd, (struct sockaddr*)&addr, &len);
	if(-1 == ret)
	{
		perror("getpeername error");
		exit(EXIT_FAILURE);
	}
	return addr;
}

void Socket::shutdownWrite()
{
	int ret;
	ret = ::shutdown(_sfd, SHUT_WR);
	if(-1 == ret)
	{
		perror("shutdown write errot");
		exit(EXIT_FAILURE);
	}
}



}
