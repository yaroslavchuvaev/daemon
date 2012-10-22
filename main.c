#include <stdio.h> 
#include <string.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <resolv.h>
#include <errno.h>
#include "authdaemon.h"

#include "service.h"

void authdaemon(void);

int main(int argc, char* argv[]) {
	if(argc==0){
		printf("%s\n", "Help");
		printf("%s\n", "--start\t-\tto launch");
		printf("%s\n", "--stop\t-\tto stop");
		printf("%s\n", "--status\t-\tto stop");
	}
	if(argc==1) {

	}

	int pid = fork();
	if(pid == -1) {
		printf("%s\n","Fork failed" );
	}
	else if(!pid) {
		if( set_pid() == 1 ) {
			printf("%s\n%s\n","Can't get access to /var/run directory.",
						"You should run daemon as root");
		}
		setsid();
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		
		authdaemon();

	}
	else {
		printf("%s\n", "Daemon started successfully");
		return 0;
	}
}