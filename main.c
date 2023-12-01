#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

// semaphore.h

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

  sem_t *semaphore;

  semaphore = sem_open("/semap1", O_CREAT, 0600, 1);
  if (semaphore == SEM_FAILED) {
    perror("sem_open failed");
    exit(EXIT_FAILURE);
  }

  struct scity *sm;
  int shmid;

  struct scity *p = (struct scity *)malloc(sizeof(struct scity));
  shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);
  if (shmid == -1) {
    perror("shmget");
  }
  printf("key of shared memory is %d\n", shmid);

  sm = (struct scity *)shmat(shmid, NULL, 0);
  
}
