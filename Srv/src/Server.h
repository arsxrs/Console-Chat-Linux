/*
 * Server.h
 *
 *  Created on: 4 Oct 2015
 *      Author: temmka
 */

#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>	/* inet(3) functions */
#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <sys/select.h>

using namespace std;

#ifndef SERVER_H_
#define SERVER_H_


class Server {
public:
	Server();
	virtual ~Server();
	void Connect();
	void process();

private:

	int					 listenfd, connfd;
	socklen_t			 clilen;
	struct sockaddr_in	 cliaddr, servaddr;

	int maxfd, sockfd, sendSock;
	int maxi;
	int nready;
	int client[FD_SETSIZE];
	fd_set rset,allset;
	ssize_t	n;


};

#endif /* SERVER_H_ */
