/**Autor: Jelsin Sanchez
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define NPHYLS 5

pthread_mutex_t chopsticks[NPHYLS];
sem_t semaphore;

void eat(long left, long right)
{
    printf("Philosopher No. %ld: state: %.10s \n", left, "eating");
    printf("Philosopher No. %ld: state: %.10s \n", right, "eating");
}

/*Threads for each philosofer*/
void *_philosopher(void *arg)
{
    long i = (long)arg;
    pthread_mutex_t *left = &chopsticks[i];
    pthread_mutex_t *right = &chopsticks[(i + 1) % NPHYLS];

    while (1)
    {
        printf("Philosopher No. %ld: state: %.10s \n", i, "thinking!");
        printf("Philosopher No. %ld: state: %.10s \n", i, "hungry!");

        sem_wait(&semaphore);

        pthread_mutex_lock(left);
        pthread_mutex_lock(right);

        eat(i, (i + 1) % NPHYLS);

        pthread_mutex_unlock(right);
        pthread_mutex_unlock(left);

        sem_post(&semaphore);

        printf("Philosopher No. %ld: state: %.10s \n", i, "done!");
    }

    return NULL;
}

int main()
{
    pthread_t philosophers[NPHYLS];
    int i;

    for (i = 0; i < NPHYLS; i++)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    sem_init(&semaphore, 0, 4);

    for (i = 0; i < NPHYLS; i++)
    {
        pthread_create(&philosophers[i], NULL, _philosopher, (void *)(intptr_t)i);
    }
    for (i = 0; i < NPHYLS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
    for (i = 0; i < NPHYLS; i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    sem_destroy(&semaphore);

    return 0;
}