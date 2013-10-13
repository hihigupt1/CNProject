/*
 * fileshare.h
 *
 *  Created on: Oct 11, 2013
 *      Author: himanshu
 */

#ifndef FILESHARE_H_
#define FILESHARE_H_
#include"ConnectionInfo.cpp"

using namespace std;

struct Drmessage
{
	string fileName;
	int numbers;
	ConnectionInfo obj[3];
};

#define BUFLEN 1024

#endif /* FILESHARE_H_ */
