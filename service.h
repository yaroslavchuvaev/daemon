
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
#include <time.h>


char *PID_FILE = "/var/run/reader.pid";

char *LOG_FILE = "/var/log/reader.log";

// файл локального сокета
char *socket_file = "/var/run/reader.socket";

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


void write_log(char *mess) {

	
	FILE *log = fopen(LOG_FILE,"a");
	time_t t = time(NULL);
	fprintf(log, "%s--%s\n\n", asctime(localtime(&t)),mess);
	fclose(log);
}


void d_exit(int status) {
	unset_pid();
	exit(status);
}




