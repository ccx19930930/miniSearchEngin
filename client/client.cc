 ///
 /// @file    client.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 23:03:33
 ///

#include "InetAddress.h"
#include "SocketIO.h"
#include <json/json.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;

int main()
{
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sfd)
	{
		perror("create socket error");
		exit(EXIT_FAILURE);
	}
	char ip[] = "192.168.188.128";
	ccx::InetAddress addr(ip, 2000);
	int ret;
	ret = connect(sfd, addr.getAddr(), addr.getAddrSize());
	if(-1 == ret)
	{
		perror("connect error");
		exit(EXIT_FAILURE);
	}

	Json::Value root;
	Json::Reader reader;
	ccx::SocketIO socketIO(sfd);	

//	char buf[1024] = "相识";
	string buf;
	cin >> buf;	
	cout << "message : " << buf << endl;
	ret = socketIO.send_protocol(buf);
	if(-1 == ret)
	{
		cout << "send" << endl;
		return -1;
	}
	ret = socketIO.recv_protocol(buf);
	if(-1 == ret)
	{
		cout << "recv" << endl;
		return -1;
	}
	if(!reader.parse(buf, root, false))
	{
		cout << "json reader parse error" << endl;
		return -1;
	}


	int size = root.size();
	for(int i = 0; i < size; ++i)
	{
		cout << "-------------------------------------------------------------------" << endl;
		cout << "title : " << root[i]["title"].asString() << endl;
		cout << "link : " << root[i]["link"].asString() << endl;
		cout << "content : " << root[i]["content"].asString() << endl;
		cout << "-------------------------------------------------------------------" << endl;
	}
}
