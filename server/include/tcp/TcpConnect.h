 ///
 /// @file    TcpConnect.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-20 11:28:17
 ///


#ifndef __TCPCONNECT_H__
#define __TCPCONNECT_H__

#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "root/Noncopyable.h"
#include "thread_pool/Task.h"

#include <memory>
#include <functional>

namespace ccx{

using std::pair;
using std::shared_ptr;
using std::function;

class TcpConnect;
typedef shared_ptr<TcpConnect> TcpConnectPtr;

class EpollPoller;

class TcpConnect
: private Noncopyable
, public std::enable_shared_from_this<TcpConnect>
{
	public:
		typedef function<void(const TcpConnectPtr & )> TcpConnectCallback;	
		
	public:	
		TcpConnect(int sfd);
		~TcpConnect();
		void send_message(const string & data);
		string recv_message();
		string getConnectInformation();	
		void shutdown();
	private:
		Socket _socket;
		InetAddress _localAddress;
		InetAddress _peerAddress;
		SocketIO _socketIO;
		bool _isShutdown;

	public:
		void handleConnection();
		void handleMessage();
		void handleClose();

		void setConnectionCallback(TcpConnectCallback cb);
		void setMessageCallback(TcpConnectCallback cb);
	//	void setSendmsgCallback(TcpConnectCallback cb);
		void setCloseCallback(TcpConnectCallback cb);

	private:

		TcpConnectCallback _onConnectCallback;
		TcpConnectCallback _onMessageCallback;
	//	TcpConnectCallback _onSendMsgCallback;
		TcpConnectCallback _onCloseCallback;

	public:
		void setEpollPollerPoint(EpollPoller * epoll);
		
		void EpollWakeup();
		void EpollPollerPush(Task task);
	private:
		EpollPoller * _epoll;

};

}

#endif
