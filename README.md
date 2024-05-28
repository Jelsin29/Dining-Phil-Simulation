# Dining-Phil-Simulation

This is an implementation of the classic Dining Philosophers problem using POSIX threads and semaphores in C.

## Problem Description

The Dining Philosophers problem is a classic synchronization problem in computer science and is used to illustrate the challenges of avoiding deadlock and starvation in concurrent systems.
The problem involves a group of philosophers sitting around a circular table, with one chopstick between each pair of philosophers. Each philosopher must alternately think and eat. However, a philosopher can only eat when they have acquired both chopsticks adjacent to them. If a philosopher cannot acquire both chopsticks, they must wait.
The challenge is to design a solution that avoids deadlock (a state where no philosopher can proceed because each is holding one chopstick and waiting for another) and starvation (a situation where a philosopher is perpetually denied access to the chopsticks).

## Solution

This implementation uses POSIX threads to represent each philosopher and a semaphore to control the number of philosophers that can eat simultaneously. The semaphore is initialized to a value of 4, allowing at most 4 philosophers to eat at the same time, thus preventing deadlock.

Each philosopher is represented by a separate thread that repeatedly goes through the following cycle:

1. Think (print "thinking!")
2. Get hungry (print "hungry!")
3. Wait on the semaphore
4. Acquire both chopsticks (left and right)
5. Eat (print "eating")
6. Release both chopsticks
7. Signal the semaphore
8. Print "done!"

The main thread creates NPHYLS (5) philosopher threads and waits for them to complete using pthread_join.
Compiling and Running
To compile the program, use a C compiler that supports POSIX threads:

    gcc -o dining_philosophers dining_philosophers.c -lpthread

Then, run the compiled executable:

    ./dining_philosophers

The program will output the states of each philosopher as they think, get hungry, eat, and finish eating.

## Note

This implementation assumes a fair semaphore implementation and does not handle philosopher starvation, which can occur if a particular philosopher is perpetually denied access to the chopsticks due to an unfair scheduling algorithm.
