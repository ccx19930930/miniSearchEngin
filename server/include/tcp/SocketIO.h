 ///
 /// @file    SocketIO.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 21:40:06
 ///

#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

#include "root/Noncopyable.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace ccx{


class SocketIO
: private Noncopyable
{
	public:
		SocketIO(int sfd);
		int send_protocol(const char *);
		int recv_protocol(char *);
	private:
		ssize_t send_n(const char *, ssize_t sise);
		ssize_t recv_n(char *, ssize_t sise);
		int _sfd;
};

}


#endif
