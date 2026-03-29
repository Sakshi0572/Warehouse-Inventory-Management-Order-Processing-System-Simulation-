/*
   processor.c
   -----------------------------------------------------------
   Reads order from pipe, processes it, updates inventory,
   and sends log message to FIFO.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "order.h"
#include "processor.h"
#include "inventory.h"

pthread_mutex_t lock;  // Mutex for thread-safe operation

// Thread function to process order
void* process_thread(void *arg) {

    int fd = *(int*)arg;   // File descriptor from pipe
    struct Order order;    // Order structure

    // Check file descriptor error
    if(fd == -1){
        printf("fd with error # %d\n", errno);
        perror("Error : ");
    }

    // Read order data from pipe
    ssize_t readBytes = read(fd, &order, sizeof(order));
    if(readBytes == -1){
        printf("read failed with error # %d\n", errno);
        perror("Error : ");
    }

    pthread_mutex_lock(&lock);  // Lock before critical section

    // Check and update inventory
    int status = check_update_stock(order.product_id, order.product_quantity);

    char msg[100];

    printf("Order received successfully\n");

    // Create log message
    sprintf(msg, "Order %d processed Quantity=%d\n",order.product_id, order.product_quantity);

    // Open FIFO and send log message
    int fifo_fd = open("myfifo", O_WRONLY);
    write(fifo_fd, msg, strlen(msg));

    printf("FIfo : %ld\n", strlen(msg));

    close(fifo_fd);  // Close FIFO

    pthread_mutex_unlock(&lock);  // Unlock after work

    return NULL;
}

// Function to create and manage processing thread
void process_order(int fd) {

    pthread_mutex_init(&lock, NULL);  // Initialize mutex

    pthread_t thread;

    // Create thread for processing
    pthread_create(&thread, NULL, process_thread, (void *)&fd);

    pthread_join(thread, NULL);  // Wait for thread to finish

    pthread_mutex_destroy(&lock);  // Destroy mutex
}
