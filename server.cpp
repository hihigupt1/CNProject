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
		this->connection.setPort(port);
		this->name = name;
	}
	virtual void startHosting() = 0;

	ConnectionInfo connection;
	string name;


};

class DirectorySrv : public Server
{
public:
	DirectorySrv(string hostname,string port, string name) : Server(hostname,port,name)
	{

	}

	void addFileHost(string name, string hostname,string port)
	{
		std::map<string,std::vector<ConnectionInfo> >::iterator it = this->mapping.find(name);
		if(it != this->mapping.end())
		{
			ConnectionInfo* fileSrv = new ConnectionInfo();
			fileSrv->setHostname(hostname);
			fileSrv->setPort(port);
			this->mapping[name].push_back(*fileSrv);
		}
		else
		{
			ConnectionInfo* fileSrv = new ConnectionInfo();
			fileSrv->setHostname(hostname);
			fileSrv->setPort(port);
			vector<ConnectionInfo> *lst = new vector<ConnectionInfo>();
			lst->push_back(*fileSrv);
			this->mapping.insert( std::pair<string,vector<ConnectionInfo> >(name, *lst));
		}

	}

	void getRegisterData(int fd)
	{
		char buf[BUFLEN] = {0};
		int count =3,recv_len;
		//keep listening for data
		while(count--)
		{
			printf("Waiting for data...");
			fflush(stdout);

			//try to receive some data, this is a blocking call
			if ((recv_len = recv(fd, buf, BUFLEN, 0)) == -1)   // read datagram from server socket
			{
				perror("recv()");
			}
			buf[recv_len-1] = '\0';
			char* file =strtok(buf," ");
			while(file != NULL)
			{
				char *host,*port;
				host = strtok(NULL," ");
				port = strtok(NULL," ");
				addFileHost(file,host,port);
				file = strtok(NULL," ");
			}

			//print details of the client/peer and the data received
			printf("Received packet from %s\n", buf);

		}

	}

	/*
	 * 1) Get Register data.
	 * 2) Start accepting client queries.
	 */
	void startHosting()
	{
		int ret = fork();
		if(ret == 0)
		{
			int fd = connection.getListeningFd("udp");
			getRegisterData(fd);
			printReg();
		}


	}

	void printReg()
	{

		typedef map<string,vector<ConnectionInfo> >::iterator MapIterator;
		for (MapIterator iter = mapping.begin(); iter != mapping.end(); iter++)
		{
			cout << "File " << iter->first << endl;

			typedef vector<ConnectionInfo>::iterator ListIterator;
			for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
			{
				ConnectionInfo *temp = &*list_iter;
				cout << " host:port" << temp->getHostname()<<":"<<temp->getPort()<<endl;

			}

		}



	}

private:
	map<string,vector<ConnectionInfo> > mapping;

};

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
	}

	void sendFileInfo(int fd)
	{
		/**
		 * Format to send <filename> <host> <port>
		 */

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
	/*
	 * 1) File open
	 * 2) Read per line.
	 * 3) Which file server, take that object and then call addtoHostFile on that object.
	 * <>.txt
	 * Server: doc1 doc2 doc3
	 */
	ifstream infile;
	infile.open("input.txt");
	cout<<"Reading from file"<<endl;
	string lineStringfromInput;
	char *stringToken;
	char dlim[] = " ";
	while(getline(infile, lineStringfromInput)){
		char* srvName;
		srvName =strtok((char* )lineStringfromInput.c_str(), dlim);
		stringToken=strtok(NULL, dlim);
		//cout<<"Number of file on server 1"<<st<<endl;
		int n = atoi(stringToken);
		if(strcmp(srvName,f1->getName().c_str()) == 0){
			for(int i= 0; i<n; i ++){
				stringToken=strtok(NULL, dlim);
				f1->addFileToHost(stringToken);
			}

		}
		else if(strcmp(srvName,f2->getName().c_str())== 0){
			for(int i =0; i<n;i++){
				stringToken=strtok(NULL,dlim);
				f2->addFileToHost(stringToken);
			}

		}
		else {
			for(int i =0; i<n;i++){
				stringToken=strtok(NULL,dlim);
				f3->addFileToHost(stringToken);
			}
		}

	}

}





int main()
{

	DirectorySrv* dr = new DirectorySrv("","8888","Dr");
	dr->startHosting();
	const ConnectionInfo *drConInfo = dr->getConnection();
	FileServer* fileSrv1 = new FileServer("","","File_Server1",*drConInfo);
	FileServer* fileSrv2 = new FileServer("","","File_Server2",*drConInfo);
	FileServer* fileSrv3 = new FileServer("","","File_Server3",*drConInfo);
	initFileSrv(fileSrv1,fileSrv2,fileSrv3);
	fileSrv1->printFileShared();
	fileSrv2->printFileShared();
	fileSrv3->printFileShared();
	fileSrv1->startHosting();
	fileSrv2->startHosting();
	fileSrv3->startHosting();
	/*
	 *client * cl1 = new client();
	 *client * cl2 = new Client();
	 */
}
