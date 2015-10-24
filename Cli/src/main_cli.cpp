
#include "Client.h"



int main(int argc, char **argv){

	Client cli;
	int ret;
	ret = cli.Connect(argc, argv);
	if(ret<0)
		cli.errMsg("Fail connection");
	cli.process();

	exit(0);
}
