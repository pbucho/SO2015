#include "pipes.h"
#include <unistd.h>
#include <errno.h>
#define __DEBUG__ 1

char errMsg[512];

void deleteFifo(char * name){
  if(unlink(name) == -1){
	if(errno == 2){
		if(__DEBUG__){
			sprintf(errMsg,	"\e[0;1;31m[ ERROR | DEBUG ]\e[0m could not remove pipe named \'%s\' due to",name);
	    	perror(errMsg);
		}
	}else{
		sprintf(errMsg,	"\e[31m[ ERROR ]\e[0m could not remove pipe named \'%s\' due to",name);
		/*printf("Pipe Name: %s ",name );
		fflush(stdout);*/
	    perror(errMsg);
		exit(EXIT_FAILURE);
	}
  }
  else{
    printf("\e[33m[ INFO  ]\e[0m pipe named \'%s\' removed with \e[32msucess\e[0m\n", name);
  }
}

void create_fifo_read(char *name){

	deleteFifo(name);

	if(mkfifo(name, S_IRUSR | S_IWUSR) != 0){
		sprintf(errMsg,	"\e[31m[ ERROR ]\e[0m Could not create FIFO named \'%s\' due to",name);
    	perror(errMsg);
	    exit(EXIT_FAILURE);
	}

	//return open_pipe_read(name);
}

void create_fifo_write(char *name){

	deleteFifo(name);

	if(mkfifo(name, S_IRUSR | S_IWUSR) != 0){
		sprintf(errMsg,	"\e[31m[ ERROR ]\e[0m Could not create FIFO named \'%s\' due to",name);
    	perror(errMsg);
	    exit(EXIT_FAILURE);
	}
	//return open_pipe_write(name);
}

int open_pipe_write(char *pipe_name){

	int shell_fifo = open(pipe_name, O_WRONLY);

	if(shell_fifo == -1){
		sprintf(errMsg,	"\e[31m[ ERROR ]\e[0m opening pipe named \'%s\' due to",pipe_name);
    	perror(errMsg);
		exit(EXIT_FAILURE);
	}

	return shell_fifo;

}

int open_pipe_read(char *pipe_name){

	int shell_fifo = open(pipe_name, O_RDONLY);

	if(shell_fifo == -1){
		sprintf(errMsg,	"\e[31m[ ERROR ]\e[0m opening pipe named \'%s\' due to",pipe_name);
    	perror(errMsg);
		exit(EXIT_FAILURE);
	}

	return shell_fifo;

}
