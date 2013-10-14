/*
 * Server1.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: Kapil
 */
#include <iostream>
#include "fileshare.h"
#include<list>
#include<map>
#include<vector>
#include<stdio.h>   //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<ctype.h>
#include<fstream>
#include <unistd.h>

using namespace std;


class FileServer : public Server
{
	ConnectionInfo dirSrv;
	vector<string> fileInfo;
public:
	FileServer(string hostname,string port, string name,const ConnectionInfo& dr) : Server(hostname,port,name)
	{
		this->dirSrv =(ConnectionInfo)dr;
		this->dirSrv.resetFd();
	}

	void addFileToHost(string fileName)
	{
		fileInfo.push_back(fileName);
	}

	void registerFilesHosted()
	{
		int fd = dirSrv.getConnectionFd("udp");
		sendFileInfo(fd);
		cout<<fd<<endl;
		dirSrv.resetFd();
	}

	void sendFileInfo(int fd)
	{
		/**
		 * Format to send <filename> <host> <port>
		 */
		string host = getConnection()->getHostIp();
		string port = getConnection()->getPort();
		string srvhost = dirSrv.getHostIp();
		string srvport = dirSrv.getPort();

		struct sockaddr_in servAddr;
		memset((char *)&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(atoi(srvport.c_str()));
		inet_aton(srvhost.c_str(), &(servAddr.sin_addr));
		char Message[BUFLEN];
		snprintf(Message,BUFLEN,"%s %s\n",this->getName().c_str(),port.c_str());
		int ret = sendto(fd,Message,strlen(Message),0,(struct sockaddr *)&servAddr,sizeof(servAddr));

	}

	void startAcceptingClientCon()
	{

	}

	/*
	 * 1) Register File hosted ie in your fileInfo.
	 * 2) Start accepting connection from clients.
	 */
	void startHosting()
	{
		registerFilesHosted();
		startAcceptingClientCon();
	}

	void printFileShared()
	{
		for ( int i = 0; i < fileInfo.size(); i++) {
			cout << fileInfo[i] << "\n ";
		}
	}
};

void initFileSrv(FileServer* f1,FileServer* f2,FileServer* f3)
{


}





int main()
{
	ConnectionInfo drConInfo;
	drConInfo.setHostname(DrSrv);
	drConInfo.setHostIp(DrSrv);
	drConInfo.setPort(DrSrvPort);
	FileServer* fileSrv1 = new FileServer(Serv1,Serv1Port,"File_Server1",drConInfo);
	FileServer* fileSrv2 = new FileServer(Serv2,Serv2Port,"File_Server2",drConInfo);
	FileServer* fileSrv3 = new FileServer(Serv3,Serv3Port,"File_Server3",drConInfo);
//
	fileSrv1->startHosting();
	fileSrv2->startHosting();
	fileSrv3->startHosting();

}
