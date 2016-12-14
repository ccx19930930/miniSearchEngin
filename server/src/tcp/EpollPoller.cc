 ///
 /// @file    EpollPoller.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-22 10:04:47
 ///


#include "tcp/EpollPoller.h"

#include <stdio.h>
#include <unistd.h>

#include <iostream>

namespace ccx{

using std::cout;
using std::endl;


EpollPoller::EpollPoller(Socket & socket)
: _epfd(epoll_create(1))
, _listenSocket(socket)
, _eventfd()
, _islooping(false)
, _fdnum(0)
, _mutex()
{
	_events.resize(1);
	AddCtl(_listenSocket.getSocket());
	AddCtl(_eventfd.getEventfd());
}

EpollPoller::~EpollPoller()
{
	::close(_epfd);
}

void EpollPoller::loop()
{
	_islooping = true;
	while(_islooping)
	{
		EpollWait();
	}
}

void EpollPoller::unloop()
{
	_islooping = false;
}


void EpollPoller::AddCtl(int fd)
{
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = fd;	
	int ret;
	ret = ::epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &event);
	if(-1 == ret)
	{
		perror("epoll add error");
		exit(EXIT_FAILURE);
	}
	++_fdnum;
}

void EpollPoller::DelCtl(int fd)
{
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = fd;	
	int ret;
	ret = ::epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &event);
	if(-1 == ret)
	{
		perror("epoll del error");
		exit(EXIT_FAILURE);
	}
	--_fdnum;
}

bool EpollPoller::isConnectionClosed(int fd)
{
	char buf[4];
	int ret;
	ret = recv(fd, buf, sizeof(buf), MSG_PEEK);
	if(-1 == ret)
	{
		perror("recv peek error");
		exit(EXIT_FAILURE);
	}
	return ret == 0;
}


void EpollPoller::handleConnection()
{
	int new_fd = _listenSocket.socketAccess();
	AddCtl(new_fd);
	TcpConnectPtr tcp(new TcpConnect(new_fd));
	tcp->setConnectionCallback(_onConnectCallback);
	tcp->setMessageCallback(_onMessageCallback);
	tcp->setCloseCallback(_onCloseCallback);
	tcp->setEpollPollerPoint(this);
	pair<int, TcpConnectPtr> temp;
	temp.first = new_fd;
	temp.second = tcp;
	_connectList.insert(temp);
	tcp->handleConnection();
}

void EpollPoller::handleMessage(int fd)
{
	bool isClose;
	isClose = isConnectionClosed(fd);
	if(isClose)
	{
		_connectList[fd]->handleClose();
		DelCtl(fd);
		_connectList.erase(fd);

	}else{
		_connectList[fd]->handleMessage();
	}
}

void EpollPoller::handlePthreadPool()
{
	safeMutex mutex(_mutex);
	uint64_t temp;
	temp = _eventfd.read();
	for(unsigned long i = 0; i < _SendList.size(); ++i)
	{
		_SendList[i]();
	}
	_SendList.clear();
}


void EpollPoller::EpollWait()
{
	int ret;
	do
	{
		ret = ::epoll_wait(_epfd, &*_events.begin(), static_cast<int>(_fdnum), 5000);
	}while(-1 == ret && errno == EINTR);	

	if(-1 == ret)
	{
		perror("epoll wait error");
		exit(EXIT_FAILURE);
	}
	else if(0 == ret)
	{
		cout << "TCP Epoll timeout" << endl;
	}else{
		for(int i = 0; i < ret; ++i)
		{
			if(EPOLLIN == _events[i].events)
			{
				if(_listenSocket.getSocket() == _events[i].data.fd)	
				{
					handleConnection();
				}else if(_eventfd.getEventfd() == _events[i].data.fd)
				{
					handlePthreadPool();
				}else{
					handleMessage(_events[i].data.fd);
				}
			}
		}
	}
}


void EpollPoller::setConnectionCallback(ConnectCallback cb)
{
	_onConnectCallback = std::move(cb);
}

void EpollPoller::setMessageCallback(ConnectCallback cb)
{
	_onMessageCallback = std::move(cb);
}

#if 0
void EpollPoller::setSendmsgCallback(ConnectCallback cb)
{
	_onSendMsgCallback = std::move(cb);
}
#endif

void EpollPoller::setCloseCallback(ConnectCallback cb)
{
	_onCloseCallback = std::move(cb);
}


void EpollPoller::wakeup()
{
	uint64_t temp = 1;
	_eventfd.write(temp);
}

void EpollPoller::PushSendList(SendCallback cb)
{
	safeMutex mutex(_mutex);
	_SendList.push_back(std::move(cb));
}


}
