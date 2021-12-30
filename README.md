# Operating Systems Assignment 3 - Bounded Buffer Problem
This exercise involves implementing the solution to the bounded buffer/readers and writers problem using threads.

You will create a program that accepts four command line arguments:
* run_time (the length of time the program should run)
* buffer_size (number of slots in the bounded buffer)
* num_producers (number of producer threads)
* num_consumers (number of consumer threads)

The program will create a thread for each producer and consumer. As each thread produces or consumes a data item, it will print its status.

## Example Output
Here are some sample runs:

### Not enough arguments
If not enough arguments are provided, the program should print an error message and exit.

```
$ ./bounded_buffer
Wrong number of arguments. Usage: bounded_buffer <run_time> <buffer_size> <num_producers> <num_consumers>
$
```
### Invalid argument
If an argument is less than or equal to 0, the program should print a message and exit
```
$ ./bounded_buffer 10 5 1 0
 ./bounded_buffer 10 5 1 0
num_consumers must be greater than 0
$
```
### Correct Arguments
```
$  ./bounded_buffer 10 5 2 2
2: slept 2, produced 11 in slot 0
2: slept 1, consumed 11 in slot 0
1: slept 2, produced 79 in slot 1
1: slept 3, consumed 79 in slot 1
1: slept 1, produced 86 in slot 2
2: slept 1, consumed 86 in slot 2
1: slept 3, produced 58 in slot 3
2: slept 2, consumed 58 in slot 3
2: slept 5, produced 72 in slot 4
1: slept 3, consumed 72 in slot 4
1: slept 1, produced 92 in slot 0
2: slept 1, produced 86 in slot 1
1: slept 1, produced 74 in slot 2
2: slept 3, consumed 92 in slot 0
$
```
## Completing the Assignment
To complete the assignment, follow the same steps that you did in [Assignment 2](https://github.com/skamens-fordham/os-hw2-template/blob/main/README.md):

1. Accept the assignment in Github Classroom via [this link](https://classroom.github.com/a/15DDe0_U)
2. Clone your repository to your local machine
3. Implement the code, following the instructions in the file `bounded_buffer.cpp`
4. Compile and test your program. 
5. Commit your changes to git (`git commit`)
6. Push your changes to github (`git push`)
7. Complete the `submit.txt` file and upload it to Blackboard
