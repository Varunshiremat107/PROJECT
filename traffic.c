// Header Files

#include <fcntl.h>     // for handling file control operations
#include <pthread.h>   // threads
#include <semaphore.h> // semaphores
#include <stdio.h>     // standard input-output operations
#include <stdlib.h>    // standard library functions
#include <string.h>    // string manipulation functions
#include <sys/shm.h>   // shared memory
#include "structure.h"

void error_handler(char *message)
{
       	perror(message);
}

// Function to capture traffic condition from camera 1

void *camera1(void *arg)
{

	char buff[5];
	struct scity *sm = (struct scity *)arg;
      	printf("Enter the traffic condition in camera 1 : \n");
	printf("High or Low\n");
	scanf("%s", buff);


      	// error handling
 
       	if (strcmp(buff, "High") == 0) {
		strcpy(sm->t1.cam1, buff);
		pthread_exit(0);	
	}
       	else if (strcmp(buff, "Low") == 0) {
	       	strcpy(sm->t1.cam1, buff);
		pthread_exit(0);
       	}
       	else {
   
	       	error_handler("Invalid Input\n");
	       	exit(0);
       	}
}


// Function to capture traffic condition from camera 2

void *camera2(void *arg) {
	char buff[5];
       	struct scity *sm = (struct scity *)arg;
       	printf("Enter the traffic condition in camera 2 : \n");
       	scanf("%s", buff);
	 // error handling
	 if (strcmp(buff, "High") == 0) {
		 strcpy(sm->t1.cam2, buff);
		 pthread_exit(0);
	 }
	 else if (strcmp(buff, "Low") == 0) {
		 strcpy(sm->t1.cam2, buff);
		 pthread_exit(0);
	 }
	 else {
		 error_handler("Invalid Input\n");
		 strcpy(sm->t1.cam2, buff);
		 pthread_exit(0);
	 }
}

// Function to capture traffic condition from camera 3
void *camera3(void *arg) {
       	char buff[5];
       	struct scity *sm = (struct scity *)arg;
       	printf("Enter the traffic condition in camera 3 : \n");
       	scanf("%s", buff);
       
	if (strcmp(buff, "High") == 0) {
	       	strcpy(sm->t1.cam3, buff);
	       	pthread_exit(0);
       	}
       	else if (strcmp(buff, "Low") == 0) {
	       	strcpy(sm->t1.cam3, buff);
	       	pthread_exit(0);
       	}
       	else {
   
	       	error_handler("Invalid Input\n");
	       	strcpy(sm->t1.cam3, buff);
	       	pthread_exit(0);
       	}
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

	   // create threads for each camera function and join them to the main thread.
	   pthread_create(&tid1, NULL, camera1, (void *)sm); // API
           pthread_join(tid1, NULL);
	   pthread_create(&tid2, NULL, camera2, (void *)sm);
	   pthread_jiioin(tid2, NULL);
	   pthread_creiiate(&tid3, NULL, camera3, (void *)sm);
	   pthread_join(tid3, NULL);
	 
	   sem_post(semaphore); // Incrementing the value of semaphore by 1
}
