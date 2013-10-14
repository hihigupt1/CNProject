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

class DirectorySrv : public Server
{
public:
	DirectorySrv(string hostname,string port, string name) : Server(hostname,port,name)
	{

	}

	void addFileHost(string name, string hostname)
	{
		std::map<string,std::vector<string> >::iterator it = this->mapping.find(name);
		if(it != this->mapping.end())
		{
			this->mapping[name].push_back(hostname);
		}
		else
		{
			vector<string> *lst = new vector<string>();
			lst->push_back(hostname);
			this->mapping.insert( std::pair<string,vector<string> >(name, *lst));
		}

	}

	void addFileServerPort(string name,string port,string ip)
	{
		ConnectionInfo info;
		info.setHostname(name);
		info.setPort(port);
		info.setHostIp(ip);
		fileSrvPortMapping.push_back(info);
	}

	void getRegisterData(int fd)
	{
		char buf[BUFLEN] = {0};
		char host[256], port[256],ip[256];
		int count =3,recv_len;
		//keep listening for data
		while(count--)
		{
			cout<<"Regestration starts"<<endl;
			fflush(stdout);

			//try to receive some data, this is a blocking call
			if ((recv_len = recv(fd, buf, BUFLEN, 0)) == -1)   // read datagram from server socket
			{
				perror("recv()");
			}
			buf[recv_len-1] = '\0';
			sscanf(buf,"%s %s\n",host,port);
			addFileServerPort(host,port,ip);

		}

	}

	void* serveClient(void* arg)
	{


	}

	/*
	 * 1) Get Register data.
	 * 2) Start accepting client queries.
	 */
	void startHosting()
	{
		int fd = connection.getListeningFd("udp");
		getRegisterData(fd);
		dumpToFile();
		cout<<"Done with Registration"<<endl;
		cout<<"Serving clients"<<endl;
		printMap();
//
//		pthread_t pid;
//
//		serveClients();
	}

	void printMap()
	{

		typedef map<string,vector<string> >::iterator MapIterator;
		for (MapIterator iter = mapping.begin(); iter != mapping.end(); iter++)
		{
			cout << "File: " << iter->first << endl;

			typedef vector<string>::iterator ListIterator;
			for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
			{
				cout<< *list_iter<<endl;

			}

		}



	}

	void dumpToFile()
	{
		/**
		 * dump to file.
		 */
		for (std::list<ConnectionInfo>::iterator it=fileSrvPortMapping.begin(); it != fileSrvPortMapping.end(); ++it)
		    std::cout <<(*it).getHostname()<<" "<<(*it).getPort()<<endl;
	}

	void initDrSrv()
	{
		ifstream infile;
		infile.open(RESOURCE_FILE);
		string lineStringfromInput;
		char *stringToken;
		char dlim[] = " ";
		while(getline(infile, lineStringfromInput)){
			char* srvName;
			srvName =strtok((char* )lineStringfromInput.c_str(), dlim);
			stringToken=strtok(NULL, dlim);
			//cout<<"Number of file on server 1"<<st<<endl;
			int n = atoi(stringToken);
			for(int i= 0; i<n; i ++){
				stringToken=strtok(NULL, dlim);
				addFileHost(stringToken,srvName);
			}

		}
	}

private:
	map<string,vector<string> > mapping;
	list<ConnectionInfo> fileSrvPortMapping;

};

int main()
{

	DirectorySrv* dr = new DirectorySrv(DrSrv,DrSrvPort,"Dr");
	dr->initDrSrv();
	dr->startHosting();
}
