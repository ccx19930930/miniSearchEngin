 ///
 /// @file    EpollPoller.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-22 09:41:04
 ///


#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__

#include "root/Noncopyable.h"
#include "Socket.h"
#include "SocketIO.h"
#include "TcpConnect.h"
#include "Eventfd.h"
#include "thread_pool/Mutex.h"
#include "thread_pool/safeMutex.h"

#include <sys/epoll.h>

#include <map>
#include <vector>

namespace ccx{

using std::map;
using std::vector;

class EpollPoller
: private Noncopyable
{
	public:
		typedef TcpConnect::TcpConnectCallback ConnectCallback;
	public:
		EpollPoller(Socket & socket);
		~EpollPoller();
		void loop();
		void unloop();
	private:
		void AddCtl(int fd);
		void DelCtl(int fd);
		void EpollWait();

		void handleConnection();
		void handleMessage(int fd);
		void handlePthreadPool();

		bool isConnectionClosed(int fd);

	private:
		int _epfd;
		Socket & _listenSocket;
		Eventfd _eventfd;
		bool _islooping;
		unsigned long _fdnum;

		typedef map<int, TcpConnectPtr> ConnectList;
		ConnectList _connectList;	

		typedef vector<struct epoll_event> EventList;
		EventList _events;

	public:
		void setConnectionCallback(ConnectCallback cb);
		void setMessageCallback(ConnectCallback cb);
		void setCloseCallback(ConnectCallback cb);

	private:
		ConnectCallback _onConnectCallback;
		ConnectCallback _onMessageCallback;
		ConnectCallback _onCloseCallback;
		
	private:
		Mutex _mutex;
	private:
		typedef function<void()> SendCallback;
		vector<SendCallback> _SendList;

	public:
		void PushSendList(SendCallback cb);
		void wakeup();

};
}
#endif
