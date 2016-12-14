 ///
 /// @file    TcpConnect.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-20 16:15:16
 ///


#include "tcp/TcpConnect.h"
#include "tcp/EpollPoller.h"

#include <string.h>
#include <sstream>
#include <string>

namespace ccx{

using std::stringstream;
using std::string;

TcpConnect::TcpConnect(int sfd)
: _socket(sfd)
, _localAddress(_socket.getLocalAddr())
, _peerAddress(_socket.getPeerAddr())
, _socketIO(sfd)
, _isShutdown(false)
{
}

TcpConnect::~TcpConnect()
{
	if(!_isShutdown)
	{
		shutdown();
	}
}

void TcpConnect::shutdown()
{
	_socket.shutdownWrite();
	_isShutdown = true;
}

void TcpConnect::send_message(const string & data)
{
	_socketIO.send_protocol(data.c_str());
}

string TcpConnect::recv_message()
{
	char data[65535];
	memset(data, 0, sizeof(data));
	_socketIO.recv_protocol(data);
	return string(data);
}

string TcpConnect::getConnectInformation()
{
	stringstream ss;
	ss << "LOCAL : " << _localAddress.getIP() << "\t" << _localAddress.getPort() << " ===== "
		<< "PEER : " << _peerAddress.getIP() <<  "\t" << _peerAddress.getPort();
	string s;
	getline(ss, s);
	return s;
}

void TcpConnect::setConnectionCallback(TcpConnectCallback cb)
{
	_onConnectCallback = std::move(cb);
}

void TcpConnect::setMessageCallback(TcpConnectCallback cb)
{
	_onMessageCallback = std::move(cb);
}

#if 0
void TcpConnect::setSendmsgCallback(TcpConnectCallback cb)
{
	_onSendMsgCallback = std::move(cb);
}

#endif
void TcpConnect::setCloseCallback(TcpConnectCallback cb)
{
	_onCloseCallback = std::move(cb);
}

void TcpConnect::handleConnection()
{
	if(_onConnectCallback)
	{
		_onConnectCallback(shared_from_this());
	}
}

void TcpConnect::handleMessage()
{
	if(_onMessageCallback)
	{
		_onMessageCallback(shared_from_this());
	}
}

void TcpConnect::handleClose()
{
	if(_onCloseCallback)
	{
		_onCloseCallback(shared_from_this());
	}
}

void TcpConnect::setEpollPollerPoint(EpollPoller * epoll)
{
	_epoll = epoll;
}

void TcpConnect::EpollWakeup()
{
	_epoll->wakeup();
}

void TcpConnect::EpollPollerPush(Task task)
{
	_epoll->PushSendList(task);
}

}
