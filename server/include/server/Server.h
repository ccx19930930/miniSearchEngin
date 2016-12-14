 ///
 /// @file    Server.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-24 10:51:09
 ///

#ifndef __SERVER_H__
#define __SERVER_H__

#include "root/Noncopyable.h"
#include "thread_pool/Thread_pool.h"
#include "tcp/TcpServer.h"
#include "GetConf.h"
#include "Query_module/QueryModule.h"
#include "Timer/TimerPtherad.h"
#include "Cache/Cache.h"


namespace ccx{

class Server
: private Noncopyable
{
	public:
		Server();

		void start();
	private:
		GetConf _conf;
		Thread_Pool _thread_pool;
		TcpServer _tcpserver;
		TimerPthread _timer;
		Cache _cache;
		QueryModule _queryModule;
	public:
		void handleConnection(const TcpConnectPtr & tcp);
		void handleMessage(const TcpConnectPtr & tcp);
		void handleClose(const TcpConnectPtr & tcp);
		void handleTimer();
		
		void handleSendmsg(const TcpConnectPtr & tcp, const string & data);
		void handleDealmsg(const TcpConnectPtr & tcp, const string & data);


};

}
#endif
