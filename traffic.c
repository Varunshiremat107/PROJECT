// Header Files

#include <fcntl.h>     // for handling file control operations
#include <pthread.h>   // threads
#include <semaphore.h> // semaphores
#include <stdio.h>     // standard input-output operations
#include <stdlib.h>    // standard library functions
#include <string.h>    // string manipulation functions
#include <sys/shm.h>   // shared memory
#include <unistd.h>
#include "structure.h"
#include <time.h>
void error_handler(char *message)
{
       	perror(message);
}
int random_input(int min ,int max)
{
       	srand(time(0));
       	return rand() %(max -min+1)+min;
}

// Function to capture traffic condition from camera 1

void camera1(void *arg)
{

	int camera1;
	struct scity *sm = (struct scity *)arg;
	camera1=random_input(1,100);
	sm->t1.cam1=camera1;
      	printf(" traffic sensed  in camera 1 : %d\n",sm->t1.cam1);
	
       	
}


// Function to capture traffic condition from camera 2

void camera2(void *arg) {
	int camera2;
       	struct scity *sm = (struct scity *)arg;
       	camera2=random_input(1,100);
	sm->t1.cam2=camera2;
      	printf(" traffic sensed  in camera 2 : %d\n",sm->t1.cam2);
	
}

// Function to capture traffic condition from camera 3
void camera3(void *arg) {
        int camera3;
       	struct scity *sm = (struct scity *)arg;
        camera3=random_input(1,100);
	sm->t1.cam3=camera3;
      	printf(" traffic sensed  in camera 3 : %d\n",sm->t1.cam3);
	
       	
}


int main() {
 
       	sem_t *semaphore;
       	int value;
       	// here we used semaphore for synchronization to ensure only one thread
        // Opening semaphore
	    semaphore = sem_open("/semap1", O_RDWR);
	    struct scity *sm;
	    int shmid;
	    char str1[10];
	    char str2[10];
	    char str3[10];
	    pthread_t tid1, tid2, tid3;

	    // Creating shared memory segement
	   shmid = shmget((key_t)1234, sizeof(struct scity), 0666);
	   sm = (struct scity *)shmat(shmid, NULL, 0);
	   sem_wait(semaphore); // Dececreasing the value of semaphore by 1
	   
	   printf("\n............Traffic Process............\n");

	   // create threads for each camera function and join them to the main thread.
	   pthread_create(&tid1, NULL, camera1, (void *)sm); // API
           pthread_join(tid1, NULL);
	   pthread_create(&tid2, NULL, camera2, (void *)sm);
	   pthread_join(tid2, NULL);
	   pthread_create(&tid3, NULL, camera3, (void *)sm);
	   pthread_join(tid3, NULL);
	 
	   sem_post(semaphore); // Incrementing the value of semaphore by 1
	   execl("./p2","p2",NULL,NULL);
}
