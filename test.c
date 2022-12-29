#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

pthread_mutex_t forks[NUM_FORKS];

void *philosopher(void *id) {
  long philosopher_id = (long)id;

  while (1) {
    printf("Philosopher %ld is thinking\n", philosopher_id);
    sleep(1);

    // Try to acquire the forks to the left and right
    if (philosopher_id % 2 == 0) {
      pthread_mutex_lock(&forks[philosopher_id]);
      pthread_mutex_lock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
    } else {
      pthread_mutex_lock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
      pthread_mutex_lock(&forks[philosopher_id]);
    }

    printf("Philosopher %ld is eating\n", philosopher_id);
    sleep(1);

    // Release the forks
    pthread_mutex_unlock(&forks[philosopher_id]);
    pthread_mutex_unlock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
  }
}

int main(int argc, char *argv[]) {
  pthread_t philosophers[NUM_PHILOSOPHERS];
  long i;

  // Initialize the forks
  for (i = 0; i < NUM_FORKS; i++) {
    pthread_mutex_init(&forks[i], NULL);
  }

  // Create a thread for each philosopher
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_create(&philosophers[i], NULL, philosopher, (void *)i);
  }
  return 1;
}
  // Wait for the philosophers to finish