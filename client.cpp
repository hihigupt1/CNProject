/*
 * Client.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: kapil
 */
#include<stdio.h>
#include <iostream>
#include "fileshare.h"

using namespace std;

class client
{
public:
	ConnectionInfo
	getDirectorySrv() const
	{
		return directorySrv;
	}

	ConnectionInfo
	getFileSrv1() const
	{
		return fileSrv1;
	}

	void
	setFileSrv1(ConnectionInfo fileSrv1)
	{
		this->fileSrv1 = fileSrv1;
	}

	ConnectionInfo
	getFileSrv2() const
	{
		return fileSrv2;
	}

	void
	setFileSrv2(ConnectionInfo fileSrv2)
	{
		this->fileSrv2 = fileSrv2;
	}

	ConnectionInfo
	getFileSrv3() const
	{
		return fileSrv3;
	}

	void
	setFileSrv3(ConnectionInfo fileSrv3)
	{
		this->fileSrv3 = fileSrv3;
	}

	client()
	{
		/*
		 * Read the file for
		 * directory server and setup the
		 * directorySrv.
		 */


	}

	int startRunning()
	{
		string fileName = "";
		ConnectionInfo* srv = this->getFileServer(fileName);
		startDocTransfer(srv);
	}

	int startDocTransfer(ConnectionInfo* fileSrv)
	{
		/**
		 * create connection with the right server
		 * calculated.
		 */

	}


	ConnectionInfo* getFileServer(string fileName)
	{
		int fd = this->directorySrv.getConnectionFd("udp");
		return getFileInfo(fd);
	}

	ConnectionInfo* getFileInfo(int filefd)
	{
		ConnectionInfo* ret = new ConnectionInfo() ;
		return ret;
	}

	string getClientName() const {
		return clientName;
	}

private:
	ConnectionInfo directorySrv;

	ConnectionInfo fileSrv1;
	ConnectionInfo fileSrv2;
	ConnectionInfo fileSrv3;
	string clientName;


	void
	setDirectorySrv(ConnectionInfo directorySrv)
	{
		this->directorySrv = directorySrv;
	}


};



