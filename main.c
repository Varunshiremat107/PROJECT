#include "headerfile.h"
#include "structure.h"
int main() 
{
  sem_t *semaphore;
  semaphore = sem_open("/semap1", O_CREAT, 0600, 1);
  if (semaphore == SEM_FAILED) 
  {
    perror("sem_open failed");
    exit(EXIT_FAILURE);
  }
  struct scity *sm;
  int shmid;
  struct scity *p = (struct scity *)malloc(sizeof(struct scity));
  shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);
  if (shmid == -1) 
  {
    perror("shmget");
  }
  else{
  printf("\n:........EMPTY STRUCTURE IN THE SHARED MEMORY CREATED........:\n");
  }
  printf("\n:...................KEY of shared memory.............:=> %d\n", shmid);
  sm = (struct scity *)shmat(shmid, NULL, 0);
  system("gcc Traffic.c -o p1");
  system("gcc Wastage.c -o p2");
  system("gcc Environment.c -o p3");
  
  system("gcc decision.c -o p4");
  system("gcc output.c -o p5");
  sleep(5);
  execl("./p1","p1",NULL,NULL);
  
}

