/*
   inventory.c
   ---------------------------------------------------
    Manages stock levels.
    Checks availability and updates stock.
*/

#include <stdio.h>
#include "inventory.h"

// Initial stock
int stock = 50;

int check_update_stock(int product_id, int quantity) {
	// Check if stock is sufficient
	if(stock >= quantity) {
		stock -= quantity;  // Update stock
		return 1;  // Success
	}
	return 0;  //Failure
}
