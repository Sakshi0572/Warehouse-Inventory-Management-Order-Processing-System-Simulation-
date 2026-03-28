/* 
   main.c
   -------------------------------------------------------------
   Entry point of Warehouse System. 
   Responsible for :
    - Creating pipe for IPC
    - Forking process
    - Calling generator(child) and processor (parent)
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include "order_generator.h"
#include "processor.h"
#include "logger.h"




// Handles signal, cleans FIFO, and exits program
void signal_handler(int sig) {
    printf("\nShutting down system...\n"); // Show shutdown message
    unlink("myfifo");                     // Delete FIFO file
    exit(0);                              // Exit program
}

int main() {
	int fd[2];
	
	signal(SIGINT, signal_handler);
	mkfifo("myfifo", 0666);
	
	//Create pipe for communication
	if (pipe(fd) == -1) {
		printf("Pipe failed with error # %d\n", errno);
		perror("Error : ");
	}
	
	pid_t pid = fork();  //Creating fork
	
	//check error
	if (pid == -1) {
		printf("Fork failed with error # %d\n", errno);
		perror("Error : ");
	}
	else if (pid == 0) {  // child process -> order generator
	
		close(fd[0]);  //close read end 
		
		generate_order(fd[1]);  //send order
		close(fd[1]);  //close write end 
                exit(0);
	}
	else {  // parent process -> order generator
	
		close(fd[1]);  //close write end 
		
		process_order(fd[0]);  //Receive and process order
		close(fd[0]);  //close read end
	}
	return 0;
}



