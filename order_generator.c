/* 
   order_generator.c
   --------------------------------------------------------------
   generate random order and sends it to processor using pipe
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include "order.h"
#include "order_generator.h"

void generate_order(int fd) {
	srand(time(NULL));     // Initialize random generator
	
	struct Order order;
	
	// Generate random product details
	order.product_id = rand() % 11 + 100;
	order.product_quantity = rand() % 10 + 1;
	strcpy(order.product_name, "Product101");
	
	if(fd == -1){
		printf("fd with error # %d\n", errno);
		perror("Error : ");
	}
	
	// Send order through pipe
	ssize_t writtenBytes = write(fd, &order, sizeof(order));
	if(writtenBytes == -1){
		printf("write failed with error # %d\n", errno);
		perror("Error : ");
	}
	else{
		printf("Order send successfully \n");
		printf("Bytes written = %ld\n", writtenBytes);
	}
}
