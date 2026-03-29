/* logger.c 
----------------------------------------- 
Logs order processing results into file. 
*/ 
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> 
#include <errno.h> 
#include "logger.h" 
   
// Start logger process 
void start_logger() { 
	char buffer[100] ={0}; // Buffer to store data read from FIFO 
  	// Open FIFO (named pipe) in read-only mode 
  	int fifo_fd = open("myfifo", O_RDONLY);
   	// Check if FIFO open failed
    if(fifo_fd == -1){
     		printf("Fifo is failed with error # %d\n", errno); 
     		perror("Error : ");
    } 
    // continuously read data
    while(1){
       		// Read data from FIFO into buffer
        	ssize_t readBytes = read(fifo_fd, buffer, sizeof(buffer)); 
        	// Check if read failed
         	if(readBytes == -1){ 
         		printf("Read failed with error # %d\n", errno);
         	 	perror("Error: "); 
       		}
       		else{
           	    continue; // one simple condition only 
       		}
            buffer[readBytes] = '\0'; 
            // Open log file in append mode ("a" → adds data without deleting old data)
            FILE *fp = fopen("store_order.log", "a"); 
            // Check if file opening failed 
            if(fp == NULL) {
              	  printf("File open failed with error # %d\n" , errno);
               	  perror("Error : ");
            } 
            else { 
            	  // Use readBytes for safety 
                  fprintf(fp, "%s", buffer); 
                  // Close file after writing 
                  fclose(fp); 
            } 
            // Print logged data on console
            printf("Logged: %s", buffer);	
	} 
       // Close FIFO 
       close(fifo_fd);
}
