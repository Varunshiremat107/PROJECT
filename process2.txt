#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
struct enviro {
  int noise;
  int air;
  char weather[10];
};

struct trf {
  char cam1[10];
  char cam2[10];
  char cam3[10];
};

struct scity {
  struct enviro e1;
  struct trf t1;
  int waste;
};

int main() {
  int shmid;
  sem_t *semaphore;
  int value;
  semaphore = sem_open("/semap1", O_RDWR);

  shmid = shmget((key_t)1234, sizeof(struct scity), 0666);
  printf("key of the shared memory is : %d\n", shmid);



  sem_getvalue(semaphore, &value);
  //printf("semaphore value before: %d\n", value);

  sem_wait(semaphore);

  sem_getvalue(semaphore, &value);
 // printf("semaphore value after : %d\n", value);


  struct scity *sm;
  sm = malloc(sizeof(struct scity));
  sm->waste = 0;
  printf("Enter the number of person adding the waste : \n");
  int person;
  scanf("%d", &person);
  for (int i = 0; i < person; i++) {
    if (sm->waste <= 100) {
      printf("\n Current percentage of waste : %d\n", sm->waste);
      printf("Remaining limit of the waste to dump : %d\n", (100 - sm->waste));
    }
    if (sm->waste >= 100) {
      printf("Waste is full, cannot dump your waste\n");
      break;
    } else {
      printf("\nEnter the percentage of waste person : %d \n ", i + 1);
      int perwaste;
      scanf("%d", &perwaste);
      sm->waste = sm->waste + perwaste;
      if (sm->waste > 100) {
        printf("Waste is full, cannot dump your waste\n");
      }
    }
    sleep(1);
  }
  if (sm->waste <= 100) {
    printf("Final waste percentage is : %d\n", sm->waste);
  }

  // free(sm);
sem_post(semaphore);
  return 0;
}
