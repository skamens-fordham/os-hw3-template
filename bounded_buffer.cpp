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

void * producer(void * arg)
{
    int myNum = producer_num.fetch_add(1) + 1;
    int sleep_time;

    while(true) {

        // Sleep for a random amount of time between 1 and 5 seconds
        sleep_time = (rand() % 5) + 1;
        sleep(sleep_time);

        // "produce" a random number between 1 and 100
        int item = (rand() % 100) + 1;

        // See if there's room for me to write
        sem_wait(&sem_empty);

        // Now that I have room to write, get the lock on the buffer
        // so I can update it. By waiting to get the lock until
        // I have passed the semaphore, I can be confident that
        // I will have a spot to write in, and I hold the lock for
        // as little time as possible

        pthread_mutex_lock(&buffer_mutex);

        buffer[next_write] = item;
        cout << myNum << ": slept " << sleep_time << ", produced " << item << " in slot " << next_write << endl;

        next_write = (next_write + 1) % buffer_size;

        sem_post(&sem_full);
        pthread_mutex_unlock(&buffer_mutex);
    }
}

void * consumer(void * arg)
{
    int myNum = consumer_num.fetch_add(1) + 1;
    int sleep_time;
    
    while(true) {
        // Sleep for a random amount of time between 1 and 5 seconds
        sleep_time = (rand() % 5) + 1;
        sleep(sleep_time);

        // Wait for there to be something for me to read
        sem_wait(&sem_full);

        // Now that I have been told there's something to 
        // read, I'll get the lock on the buffer
        // so I can read it. By waiting to get the lock until
        // I have passed the semaphore, I can be confident that
        // there will be something for me to read and I 
        // minimize the time spent holding the lock

        pthread_mutex_lock(&buffer_mutex);

        int item = buffer[next_read];
        cout << myNum << ": slept " << sleep_time << ", consumed " << item << " in slot " << next_read << endl;
        next_read = (next_read + 1) % buffer_size;

        sem_post(&sem_empty);
        pthread_mutex_unlock(&buffer_mutex);
    }
}


int main(int argc, char ** argv)
{
    // Usage: bounded_buffer <run_time> <buffer_size> <num_producers> <num_consumers>

    if (argc != 5) {
        cerr << "Wrong number of arguments. Usage: bounded_buffer <run_time> <buffer_size> <num_producers> <num_consumers>" << endl;
        exit(1);
    }

    run_time = atoi(argv[1]);
    if (run_time <=0) {
        cerr << "run_time must be greater than 0" << endl;
        exit(2);
    }


    buffer_size = atoi(argv[2]);
     if (buffer_size <=0) {
        cerr << "buffer_size must be greater than 0" << endl;
        exit(3);
    }   

    int num_producers;
    num_producers = atoi(argv[3]);
    if (num_producers <= 0) {
        cerr << "num_producers must be greater than 0" << endl;
        exit(4);
    }

    int num_consumers;
    num_consumers = atoi(argv[4]);
    if (num_producers <= 0) {
        cerr << "num_producers must be greater than 0" << endl;
        exit(5);
    }

    buffer = new int[buffer_size];

    // Initialize the semaphores
    sem_init(&sem_empty, 0, buffer_size);
    sem_init(&sem_full, 0, 0);


    // Initialize the random number generator
    srand(time(NULL));

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


    sleep(run_time);
    exit(0);
}