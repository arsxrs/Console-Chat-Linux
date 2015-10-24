/*
 * Client.cpp
 *
 *  Created on: 4 Oct 2015
 *      Author: temmka
 */

#include "Client.h"
using namespace std;

struct Msg
{
	char nick[24];
	char msg[1000];
};

Msg snd, rcv;
int sockfd;
pthread_attr_t attr;
struct sockaddr_in	servaddr;

Client::Client() {

}

Client::~Client() {

}

void Client::errMsg(const char *msg){

	std::cout<<msg<<std::endl;
	exit(1);

}

int Client::Connect(int argc, char **argv){
	int ret;

	if (argc != 3)
		errMsg("missing server IP or port ");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
		errMsg("socket error");

	while(1){
		std::string input;
		cout<< "enter your nick: ";
		cin>>input;

		if(input.length()>24){
			cout<< "login must be < 24" <<endl;
		}
		else{
			sprintf(snd.nick,"%s",input.c_str());
			break;
		}
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(atoi(argv[2]));	/* daytime server */
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	ret = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	return ret;
}


int Client::process(){

	rc = pthread_create(&thread2, NULL, thread_sendMsg,  (void*)id2);
	rc = pthread_create(&thread1, NULL, thread_getMsg, (void*) id1);

	for(;;) {

	}
}

void Client::sendMsg(void ){

	for(;;){

		cin.getline(snd.msg,sizeof(snd.msg));
		cout<< snd.nick << "->" << snd.msg << endl;
		write(sockfd,(void*)&snd, 1024);

	}
}

void Client::getMsg(void ){

	while (1){
		if ( read(sockfd, &rcv, 1024)){
			cout << rcv.nick << "-> " << rcv.msg << endl;
		}
	}
}


void *Client::thread_sendMsg(void *threadid){
	static_cast<Client*>(threadid)->sendMsg();
	return NULL;
}

void *Client::thread_getMsg(void *threadid){
	static_cast<Client*>(threadid)->getMsg();
	return NULL;
}

