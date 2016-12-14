 ///
 /// @file    SocketIO.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 21:40:06
 ///

#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

namespace ccx{
using std::string;
class SocketIO
{
	public:
		SocketIO(int sfd);
		int send_protocol(string & data);
		int recv_protocol(string & data);
	private:
		ssize_t send_n(const char *, ssize_t sise);
		ssize_t recv_n(char *, ssize_t sise);
		int _sfd;
};

}


#endif
