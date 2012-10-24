#include <stdio.h> 
#include <stdlib.h> 
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
#include <openssl/md5.h>

char *soket_file = "/var/run/reader.socket";
char *key = "sI4HAyNBA0@R!?DD";

#define hashlen MD5_DIGEST_LENGTH



char *hash(char *input) {

	unsigned char digest[MD5_DIGEST_LENGTH];

	int len = strlen(input)+strlen(key);
	char *str = malloc(len+1);

	strcpy(str,input);
	strcat(str,key);
	MD5(str,len,digest)

	free (str);
	return digest;
}

void authdaemon(void) {

	sleep(60);
	int sock = socket(AF_UNIX,SOCK_STREAM,IPPROTO_TCP);
	if(sock < 0) {
		write_log("socket error");
		exit(1);
	}
	struct sockaddr sa;
	sa.sa_family = AF_UNIX;
	strcpy(sa.sa_data,soket_file);
	int res = bind(sock,&sa,
		strlen(sa.sa_data) + sizeof(sa.sa_family));
	if(res<0){
		write_log("socket bind error");
		exit(1);
	}

	listen(sock,100);

	while(1){
		int current_socket = accept(sock,NULL,NULL);
		if(current_socket<1){
			write_log("socket accept error");
			continue;
		}	
		char *buffer = malloc(2048);

		int bytes_read = recv(current_socket,buffer,2048,0);
		if(bytes_read <=0) {
			free(buffer);
			write_log("socket read error");
			continue;
		}
		send(current_socket,hash(buffer),hashlen,0);

		free(buffer);

		close(current_socket);


	}
	
}


