
/* управление pid-файлом и логами*/


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


char *PID_FILE = "/var/run/reader.pid";

int  set_pid() {
	FILE *pid_file = fopen(PID_FILE,"w");
	if(pid_file) 	{
		fprintf(pid_file, "%u", getpid());
		fclose(pid_file);
		return 0;
	}
	return 1;
}

unsigned int get_pid() {
	FILE *pid_file = fopen(PID_FILE,"r");
	unsigned int pid;
	if(pid_file) 	{
		fscanf(pid_file, "%u", &pid);
		fclose(pid_file);
		return pid;
	}
	return 0;
}
int unset_pid() {
	unlink(PID_FILE);
	return 0;
}


void write_log(char *) {

}




