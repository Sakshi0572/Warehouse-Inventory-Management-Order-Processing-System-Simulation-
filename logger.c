/*
   logger.c
   -----------------------------------------
   Logs order processing results into file.
*/
#include <stdio.h>
#include "logger.h"
#include <errno.h>
void log_order(int product_id, int quantity, int status) {
	// Open log file in append mode
	FILE *fp = fopen("orders.log", "a");
	
	if(fp == NULL) {
		printf("File open failed with error # %d\n" , errno);
		perror("Error : ");
	}
	// Write result into file
	if(status) {
		fprintf(fp, "Order %d Success Qunatity : %d\n", product_id, quantity);
	}
	else{
		fprintf(fp, "Order %d Failed Qunatity : %d\n", product_id, quantity);
	}
	fclose(fp);   //Close file
}
