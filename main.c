/*  фронт-энд демона */



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


#include "service.h"
#include "authdaemon.h"


void print_help(void);
void print_error(char*);


// Точка входа приложения
int main(int argc, char* argv[]) {

	// проверяем на root
	if(getuid() != 0){
		print_error("You should run daemon as root");

		return 1;

	}

	
	// Делаем разбор аргументов командной строки

	// Если пользователь ничего не ввел, выводим подсказку
	if(argc==1){
		print_help();
		return 0;
	}
	if(argc==2) {

		if( strcmp(argv[1],"--help") == 0 ) {
			// выводим подсказку
			print_help();
			return 0;
		}

		else if( strcmp(argv[1],"--stop") == 0) {
			unsigned int pid = get_pid();
			kill(pid, SIGTERM);
			printf("%s\n", "stop");
			unset_pid();
		}
			
	
		else if( strcmp(argv[1],"--start") == 0 ) {
			// запускаем демон

			unsigned int pid; // идентификатор дочернего процесса

			// проверяем наличие файла блокировки
			if( get_pid() != 0) {

				print_error("Daemon is already running.");

				return 1;
			}
			
			// форк, stdio & stdout & sterr > /dev/null, рабочий каталог - /

			pid = daemon(1,1);

			set_pid(pid);

			//!! с этого момента управление у дочернего процесса

			if(pid == -1) {
				printf("%s\n","Fork failed" );
				return 1;
			}
			
			// далее логика работы демона
			authdaemon();

			// удаляем файл
			unset_pid();
			
			}
	
	}
	return 0;
}

// выводит сообщние-подсказку
void print_help() {
	printf("\n%s\n", "Help");
	printf("%s\n", "Use next options:");
	printf("%s\n", "--start\t\t-\tto launch");
	printf("%s\n", "--stop\t\t-\tto stop");
	printf("%s\n", "--status\t-\tto view status");
	printf("\n");
}

void print_error(char *error) {
	printf("[ERROR]\t%s\n",error);

}