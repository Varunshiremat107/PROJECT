#include <fcntl.h>
#include <pthread.h>
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


void *camera1(void *arg) {
  struct scity *sm = (struct scity *)arg;
  printf("enter the traffic condition in camera 1 : \n");
  scanf("%s", sm->t1.cam1);
  pthread_exit(0);
}

void *camera2(void *arg) {
  struct scity *sm = (struct scity *)arg;
  printf("enter the traffic condition in camera 2 : \n");
  scanf("%s", sm->t1.cam2);
  pthread_exit(0);
}

void *camera3(void *arg) {
  struct scity *sm = (struct scity *)arg;
  printf("enter the traffic condition in camera 3 : \n");
  scanf("%s", sm->t1.cam3);
  pthread_exit(0);
}

int main() {
  sem_t *semaphore;
  int value;
  semaphore = sem_open("/semap1", O_RDWR);

  struct scity *sm;
  int shmid;
  char str1[10];
  char str2[10];
  char str3[10];
  pthread_t tid1, tid2, tid3;

  shmid = shmget((key_t)1234, sizeof(struct scity), 0666);
  printf("key of the shared memory is : %d\n", shmid);
  sm = (struct scity *)shmat(shmid, NULL, 0);

sem_getvalue( semaphore ,&value);
//printf("\n Semphore val before entering critical section=(%d)\n",value);

 sem_wait(semaphore);

 sem_getvalue( semaphore ,&value);
 //printf("\n Semphore val after entering critical section=(%d)\n",value);

  pthread_create(&tid1, NULL, camera1, (void *)sm);
  pthread_join(tid1, NULL);
  pthread_create(&tid2, NULL, camera2, (void *)sm);
  pthread_join(tid2, NULL);
  pthread_create(&tid3, NULL, camera3, (void *)sm);
  pthread_join(tid3, NULL);


  sem_post(semaphore);
}

