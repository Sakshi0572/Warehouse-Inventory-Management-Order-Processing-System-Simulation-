/*
   processor.c
   -----------------------------------------------------------
   Receives order from pipe, processes it,
   checks inventory, and logs the result.
*/
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "order.h"
#include "processor.h"
#include "inventory.h"
#include "logger.h"

void process_order(int fd) {
	struct Order order;
	
	if(fd == -1){
		printf("fd with error # %d\n", errno);
		perror("Error : ");
	}
	
	// Read order from pipe
	ssize_t readBytes = read(fd, &order, sizeof(order));
	if(readBytes == -1){
		printf("read failed with error # %d\n", errno);
		perror("Error : ");
	}
	else{
		printf("Order received successfully \n");
		printf("Product ID : %d\n", order.product_id);
		printf("Product Qunatity : %d\n", order.product_quantity);
		
		// Check stock availability
		int status = check_update_stock(order.product_id, order.product_quantity);
		
		// Log result
		log_order(order.product_id, order.product_quantity, status);
		
		// Display result
		if(status) {
			printf("Order Processed Successfully\n");
		}
		else{
			printf("Order Failed (Stock not available)\n");
		}
	}
}
