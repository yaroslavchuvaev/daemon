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

// устанавливаем длину хэша
#define hashlen MD5_DIGEST_LENGTH



// настройки 


// включаем файл с ключем
#include "key.h"



// длина очереди на подключение
int QUERY_LENGTH = 100;




// функция рассчета хэша
char *hash(char *input) {

	// статический буфер под хэш
	unsigned char *digest = malloc(MD5_DIGEST_LENGTH);
	// буфер под хэшируемое значение (входная строка + ключ)
	int len = strlen(input)+strlen(key);
	char *str = malloc(len+1);
	strcpy(str,input);
	strcat(str,key);

	// получаем хэш
	MD5(str,len,digest);
	// очищаем память
	free (str);
	return digest;
}

// функция, которая собственно реализует логику работы демона

void authdaemon(void) {


	// создаем локальный сокет
	int sock = socket(AF_UNIX,SOCK_STREAM,0);

	// записываем лог об ошибке
	if(sock < 0) {
		write_log("socket error");
		d_exit(1);
	}
	write_log("socket created");

	// указываем "сетевой" адрес
	struct sockaddr_un sa;
	sa.sun_family = AF_UNIX;
	strcpy(sa.sun_path,socket_file);

	// привязка сокета
	int res = bind(sock,&sa,
		strlen(sa.sun_path) + sizeof(sa.sun_family));
	if(res<0){
		write_log("socket bind error");
		d_exit(1);
	}
	write_log("soket binded");

	// установка сокета на прослушивание
	listen(sock,QUERY_LENGTH);

	// запускаем цикл обработки
	while(1){
		// достаем из очереди сокет подключения
		int current_socket = accept(sock,NULL,NULL);
		if(current_socket<0){
			write_log("socket accept error");
			continue;
		}	

		// буфер под входную строку
		char *buffer = malloc(2048);

		// считываем данные
		int bytes_read = recv(current_socket,buffer,2048,0);
		if(bytes_read <=0) {
			free(buffer);
			write_log("socket read error");
			continue;
		}
		// рассчитывем хэш
		char *digest = hash(buffer);

		// перевод в HEX-строку
		int i= 0;
		for(; i < MD5_DIGEST_LENGTH; i++)
    		sprintf(&buffer[2*i], "%02X", digest[i]);

		send(current_socket,buffer,hashlen*2,0);
		// освобождаем память из-под буфера и хэша
		free(buffer);
		free(digest);
		// закрываем текущее подключение
		close(current_socket);


	}
	
}


