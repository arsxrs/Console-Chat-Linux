/*
 * Server.cpp
 *
 *  Created on: 4 Oct 2015
 *      Author: temmka
 */

#include "Server.h"

struct Msg
{
	char nick[24];
	char msg[1000];
};

Msg rcv;


Server::Server() {

}

Server::~Server() {

}

void Server::Connect(){

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr,0,  sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(9877);

	bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	listen(listenfd, 1024);

	maxfd= listenfd;
	maxi=-1;

	for(int i=0; i<FD_SETSIZE; i++){
		client[i]=-1;
	}

	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);
}

void Server::process(){
	int i;
	for ( ; ; ) {
		rset = allset;
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if (FD_ISSET(listenfd, &rset)) {

			cout << "New connection" <<endl;

			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen);

			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] < 0) {
					client[i] = connfd;	/* save descriptor */
					break;
				}
			if (i == FD_SETSIZE)
				cout<<"too many clients"<<endl;

			FD_SET(connfd, &allset);	/* add new descriptor to set */
			if (connfd > maxfd)
				maxfd = connfd;			/* for select */
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

		for (i = 0; i <= maxi; i++) {	/* check all clients for data */
			if ( (sockfd = client[i]) < 0)
				continue;

			if (FD_ISSET(sockfd, &rset)) {
				if ( (n = read(sockfd, &rcv, 1024)) == 0) {

					close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
					cout << "Close connection" <<endl;

				} else{

					cout<< rcv.nick << "->" << rcv.msg << endl;

					for (int j = 0; j <= maxi; j++) {
						sendSock = client[j];
						if (j!=i)
							send(sendSock, (void*)&rcv, 1024,0);
					}
				}
				if (--nready <= 0)
					break;				/* no more readable descriptors */
			}
		}
	}

}


