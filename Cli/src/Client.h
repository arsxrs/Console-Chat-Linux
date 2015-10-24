/*
 * Client.h
 *
 *  Created on: 4 Oct 2015
 *      Author: temmka
 */

#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/types.h>	/* basic system data types */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include <pthread.h>

#include <sstream>

#include <fcntl.h>
#include <sys/select.h>

#ifndef CLIENT_H_
#define CLIENT_H_


void sendMsg(void);

void *etMsg(void);



class Client {
public:
	Client();
	virtual ~Client();

	int Connect(int argc, char **argv);
	int Disconnect();
	void errMsg(const char *msg);
	int setName();
	void sendMsg();
	void getMsg();
	int printMsg();

	static void *thread_sendMsg(void *threadid);
	static void *thread_getMsg(void *threadid);
	int id1,id2;
    int result;
    int rc;
	pthread_t thread1, thread2;


	int process();






};

#endif /* CLIENT_H_ */
