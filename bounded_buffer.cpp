#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>

#include <pthread.h>
#include <semaphore.h>
#include <atomic>

using namespace std;

// The length of time the program should run
int run_time;

// The buffer that will be produced into and consumed from. 
int *buffer;
int buffer_size;

// The number of producers and consumers we will have
int num_producers;
int num_consumers;

// TODO: Declare the semaphores that you will need to implement this algorithm
//       Semaphores are of type sem_t

// TODO: Declare a mutex that you will use in your implementation.
//       Use type pthread_mutex_t

// TODO: Declare any other global variables you will need to 
//       use to implement your algorithm



// These atomic variables will be used simply to generate unique numbers
// to identify each thread.
atomic_int producer_num(0);
atomic_int consumer_num(0);



// This is the function that will be executed by each producer thread.
void * producer(void * arg)
{

    // Set my unique thread number, to be used in the output statements below.
    int myNum = producer_num.fetch_add(1) + 1;
 
    while(true) {

        // TODO: Sleep for a random amount of time between 1 and 5 seconds
        //       Make sure to save the amount of time that was slept, so it can 
        //       be printed out below.



        int item;

        // TODO: "Produce" an item by generating a random number between 1 and 100 and 
        //       assigning it to "item"

        

        // TODO: Implement the meat of the producer algorithm, using any semaphores and
        //       mutex locks that are needed to ensure safe concurrent access.
        //
        //       After producing your item and storing it in the buffer, print a line
        //       in the following format:
        //
        //       <myNum>: slept <seconds>, produced <item> in slot <buffer slot>
        //
        //       For example: 
        //       7: slept 5, produced 27 in slot 2

    }

}

void * consumer(void * arg)
{
    // Set my unique thread number, to be used in the output statements below.
    int myNum = consumer_num.fetch_add(1) + 1;
    
    while(true) {

        // TODO: Sleep for a random amount of time between 1 and 5 seconds
        //       Make sure to save the amount of time that was slept, so it can 
        //       be printed out below.

        
        // The item that will be consumed
        int item;
        
        // TODO: "Produce" an item by generating a random number between 1 and 100 and 
        //       assigning it to "item"

        

        // TODO: Implement the meat of the consumer algorithm, using any semaphores and
        //       mutex locks that are needed to ensure safe concurrent access.
        //
        //       After consuming your item and storing it in "item", print a line
        //       in the following format:
        //
        //       <myNum>: slept <seconds>, produced <item> in slot <buffer slot>
        //
        //       For example: 
        //       2: slept 3, consumed 22 from slot 2



    }
}


int main(int argc, char ** argv)
{
    // Usage: bounded_buffer <run_time> <buffer_size> <num_producers> <num_consumers>


    // TODO: Process the command line arguments. If there are not enough arguments, or if any of the 
    //       arguments is <= 0, exit with an error message.
    


    // TODO: Allocate your buffer as an array of the correct size based on the command line argument
    

    // TODO: Initialize the semaphore(s) you are using in your algorithm.
    //       Use the function sem_init() - see https://man7.org/linux/man-pages/man3/sem_init.3.html
    //   


    // Initialize the random number generator (see https://man7.org/linux/man-pages/man3/srand.3.html)
    srand(time(NULL));


    // Start the producer and consumer threads.

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0; i < num_producers; ++i) {
        pthread_t thread_id;
        pthread_create(&thread_id, &attr, producer, NULL);
    }

    for (int i = 0; i < num_consumers; ++i) {
        pthread_t thread_id;
        pthread_create(&thread_id, &attr, consumer, NULL);
    }


    // Now the main program sleeps for as long as the program is supposd to run (based on the command line
    // argument). While the main thread is sleeping, all of the child threads will be busily producing and consuming.
    sleep(run_time);

    // When the main program is done sleeping, we exit. This will cause all the threads to exit.
    // In other applications, the main program might want to wait for the child threads to complete. 
    // This is accomplished with the pthread_join() function (https://man7.org/linux/man-pages/man3/pthread_join.3.html)
    exit(0);
}