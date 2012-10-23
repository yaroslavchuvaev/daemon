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
	
	if(argc==1){
		printf("\n%s\n", "Help");
		printf("%s\n", "Use nex options:");
		printf("%s\n", "--start\t\t-\tto launch");
		printf("%s\n", "--stop\t\t-\tto stop");
		printf("%s\n", "--status\t-\tto stop");
		printf("\n");
		return 0;
	}
	if(argc==2) {
		if( strcmp(argv[1],"--start") == 0 ) {
			unsigned int pid = fork();
			if(pid == -1) {
				printf("%s\n","Fork failed" );
				return 1;
			}
			else if(!pid) {
				if( set_pid() == 1 ) {
					printf("\n%s\n%s\n\n","[ERROR]\tCan't get access to /var/run directory.",
								" * You should run daemon as root");
					return 1;
				}
				setsid();
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				close(STDERR_FILENO);
				sigset_t sigset;

				authdaemon();

				unset_pid();
				return 0;

			}
			else {
				printf("%s\n", "Daemon started successfully");
				return 0;
			}
		}
		else if( strcmp(argv[0],"--stop") == 0 ) {
			unsigned int pid = get_pid();
			kill(pid, SIGTERM);
			printf("%s\n", "stop");
		}
	}

	
}