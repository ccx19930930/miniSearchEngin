 ///
 /// @file    Server.cc
 /// @author  ccx(chenchengxi993@gmail.com)
 /// @date    2016-11-24 11:16:15
 ///


#include "server/Server.h"

#include <functional>

namespace ccx{


using namespace std::placeholders;
using std::bind;

Server::Server()
: _conf()
, _thread_pool(_conf.getPthreadNum(), _conf.getMaxQueueNum())
, _tcpserver(_conf.getIP(), _conf.getPort())
, _timer()
, _cache(_conf.getPthreadNum())
, _queryModule(_cache)
{
	_tcpserver.setConnectionCallback(bind(&Server::handleConnection, this, _1));
	_tcpserver.setMessageCallback(bind(&Server::handleMessage, this, _1));	
	_tcpserver.setCloseCallback(bind(&Server::handleClose, this, _1));
	_timer.setTimeCallback(bind(&Server::handleTimer, this));
	_timer.start();
}

void Server::start()
{
	_thread_pool.start();
	_tcpserver.start();
}


void Server::handleConnection(const TcpConnectPtr & tcp)
{
	cout << "login -----> "
		<< tcp->getConnectInformation() << endl;
}

void Server::handleMessage(const TcpConnectPtr & tcp)
{
	string data;
	data = tcp->recv_message();
	_thread_pool.recvTask(bind(&Server::handleDealmsg, this, tcp, data));
}

void Server::handleSendmsg(const TcpConnectPtr & tcp, const string & data)
{
	tcp->send_message(data);	
}

void Server::handleDealmsg(const TcpConnectPtr & tcp, const string & data)
{
	cout << "message : " << data << endl;
	string data_dealed = "no such key";
	_queryModule.do_Query(data_dealed, data);
//	cout << "send : " << data_dealed << endl;


	tcp->EpollPollerPush(bind(&Server::handleSendmsg, this, tcp, data_dealed));
	tcp->EpollWakeup();
}

void Server::handleClose(const TcpConnectPtr & tcp)
{
	cout << "logout -----> "
		<< tcp->getConnectInformation() << endl;
}

void Server::handleTimer()
{
	_cache.synchronization();
	cout << "timer" << endl;
}


}
