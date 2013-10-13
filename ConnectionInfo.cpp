/*
 * Connection.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: Kapil
 *      This file contains the connection info.
 *
 */


#include<string>
#include<iostream>
#include<error.h>
#include<stdio.h>   //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<ctype.h>
#include <unistd.h>

using namespace std;

class ConnectionInfo{
public:
	ConnectionInfo()
	{
		fd = -1;
	}
	string getHostIp() const
	{
		return hostIp;
	}


	string getHostname() const
	{
		return hostname;
	}


	string getPort() const
	{
		return port;
	}
	int getConnectionFd(string type)
	{
		return -1;
	}

	int getListeningFd(string type)
	{
		struct sockaddr_in si_me;
		if(fd != -1)
			return fd;

		if(type == "udp")
		{
			int  i;
			//create a UDP socket
			if ((fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
			{
				perror("socket");
			}

			// zero out the structure
			memset((char *) &si_me, 0, sizeof(si_me));

			si_me.sin_family = AF_INET;
			si_me.sin_port = htons(atoi(this->getPort().c_str()));
			si_me.sin_addr.s_addr = htonl(INADDR_ANY);

			//bind socket to port
			if( bind(fd , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
			{
				perror("bind");
			}
		}
		else
		{





		}
		return fd;
	}

	void setHostIp(string hostIp)
	{
		this->hostIp = hostIp;
	}
	void setPort(string port)
	{
		this->port = port;
	}

	void setHostname(string hostname)
	{
		this->hostname = hostname;
	}

	int getFd() const {
		return fd;
	}

	void resetFd()
	{
		close(fd);
		fd = -1;
	}




private:
	string hostname;
	string hostIp;
	string port;
	int fd;
};
