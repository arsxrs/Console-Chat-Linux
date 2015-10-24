
#include	<time.h>
#include "Server.h"



int
main(int argc, char **argv)
{
		Server srv;

		srv.Connect();
		srv.process();

	return 0;
}
