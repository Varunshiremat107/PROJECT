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


void noise_entry(struct scity *sm)
{
  printf("enter the noise in DB: \n");
  scanf("%d", &sm->e1.noise);
}

void air_entry(struct scity *sm) 
{
  printf("enter the air in DB: \n");
  scanf("%d", &sm->e1.air);
}

void weather_entry(struct scity *sm)
{
  char weat1[10];
  printf("Enter the Weather condition : \n");
  scanf("%s", weat1);
  int len2 = strlen(weat1);

  strcpy((sm->e1.weather), weat1);
}




int main() {

  struct scity *sm;
  int shmid;
  int val;
  sem_t *semaphore;
  semaphore = sem_open("/semap1", O_RDWR);
  //char air1[10];

  shmid = shmget((key_t)1234, 1024, 0666);
  printf("key of the shared memory is : %d\n", shmid);
  sm = (struct scity *)shmat(shmid, NULL, 0);
  sem_getvalue(semaphore, &val);
  printf("value before %d\n", val);
  sem_wait(semaphore);
  sem_getvalue(semaphore, &val);


   noise_entry(sm);
   air_entry(sm);
    weather_entry(sm);

  sem_post(semaphore);
  printf("value after %d\n", val);
}
