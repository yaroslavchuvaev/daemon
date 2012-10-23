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
#include <pthread.h>

void *work_thread(void *);

void authdaemon(void)
{
	pthread_t thread;
	sigset_t sigset;
	int signo;


	pthread_create(&thread, NULL, work_thread, NULL);

	sigaddset(&sigset, SIGTERM);

	while(1){
		sigwait(&sigset, &signo);
		if (signo == SIGTERM) {
			pthread_kill(thread, SIGTERM);
			break;
		}
	}
}

void *work_thread(void *th_args) {
	while(1){
		
	}
}