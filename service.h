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

int  set_pid() {
	FILE *pid_file = fopen("/var/run/reader.pid","w+");
	if(pid_file) 	{
		fprintf(pid_file, "%u", getpid());
		fclose(pid_file);
		return 0;
	}
	return 1;
}

unsigned int get_pid() {
	FILE *pid_file = fopen("/var/run/reader.pid","r+");
	unsigned int pid;
	if(pid_file) 	{
		fscanf(pid_file, "%u", &pid);
		fclose(pid_file);
		return 0;
	}
	return 0;
}