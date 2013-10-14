/*
 * fileshare.h
 *
 *  Created on: Oct 11, 2013
 *      Author: himanshu
 */

#ifndef FILESHARE_H_
#define FILESHARE_H_
#include"ConnectionInfo.cpp"
#define Serv1 "127.0.0.1"
#define Serv1Port "8881"
#define Serv2 "127.0.0.1"
#define Serv2Port "8882"
#define Serv3 "127.0.0.1"
#define Serv3Port "8883"
#define DrSrv "127.0.0.1"
#define DrSrvPort "8888"
#define RESOURCE_FILE "resource.txt"

using namespace std;

struct Drmessage
{
	string fileName;
	int numbers;
	ConnectionInfo obj[3];
};


class Server
{
public:
	const ConnectionInfo* getConnection() const {
		return &connection;
	}

	string getName() const {
		return name;
	}

	Server(string hostName, string port, string name)
	{
		this->connection.setHostname(hostName);
		this->connection.setHostIp(hostName);
		this->connection.setPort(port);
		this->name = name;
	}
	virtual void startHosting() = 0;

	ConnectionInfo connection;
	string name;


};

#define BUFLEN 1024

#endif /* FILESHARE_H_ */
