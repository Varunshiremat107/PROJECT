#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <unistd.h>
#include "structure.h"

int random_input(int min ,int max)
{
       	srand(time(0));
	return rand() %(max -min+1)+min;
}

void Error_Handler(char *message) {
       	perror(message);
}

// Sensor input of Noise

void *Noise_Condition(void *arg) 
{
       	struct scity *sm = (struct scity *)arg;
       	int input1;
       	printf("\nEnter Noise data in Decible: \n");
       	input1=random_input(1,500);
       	sm->e1.noise=input1;
       	return NULL;
}

// Entering the air condition input

void *Air_Condition(void *arg) {
       	struct scity *sm = (struct scity *)arg;
       	int input2;
       	printf("\nEnter AQI: \n");
       	input2=random_input(1,500);
       	sm->e1.air=input2;
       	return NULL;
}

// Entering the weather input

void *Weather_Condtion(void *arg) {
       	struct scity *sm = (struct scity *)arg;
       	char input[10];
       	printf("\nEnter the Weather Condition from below  : \n");
	printf("Cloudy \n");
       	printf("Rainy \n");
       	printf("Clear \n");
       	scanf("%s", input);
       
	if ((strcmp(input, "Cloudy") == 0) || (strcmp(input, "Rainy") == 0) || (strcmp(input, "Clear") == 0)) {
	       	strcpy((sm->e1.weather), input);
       	} 
	else {
	       	Error_Handler("Error:Invalid input");
	       	strcpy((sm->e1.weather), input);
       	}
	return NULL;
}

// storing data in file for backup

void File_Store(struct scity *sm) {
       	FILE *fp;
       	fp = fopen("data1.txt", "a");
       
	if (fp == NULL) {
	       	perror("ERROR OPEING FILE");
	       	exit(1);
	}

       	fprintf(fp, "noise:%d  \n", sm->e1.noise);
       	fprintf(fp, "air:%d  \n", sm->e1.air);
       	fprintf(fp, "weather:%s  \n", sm->e1.weather);
       	fclose(fp);
}

int main() {

        printf("\n............Environment Process............\n");

       	pthread_t tid1, tid2, tid3;
       	struct scity *sm; // structure pointer
        int shmid;        // shared memory id 
		         //int val;
        sem_t *semaphore;                        // semaphore pointer
        semaphore = sem_open("/semap1", O_RDWR); // opening semaphore
						 
        if (semaphore == SEM_FAILED) {
	       	Error_Handler("semaphore initialization failed");
       	}
       
	shmid = shmget((key_t)1234, 1024, 0666); // opening shared memory
        if (shmid == -1) {
	       	Error_Handler("shmget failed");
       	}
       	printf("key of the shared memory is : %d\n", shmid);
       	sm = (struct scity *)shmat(shmid, NULL,0); // attaching shared memory to the process

       	sem_wait(semaphore); // waiting for semaphore
       	pthread_create(&tid1, NULL, Noise_Condition, (void *)sm); // API
       	pthread_join(tid1, NULL);
       	pthread_create(&tid2, NULL, Air_Condition, (void *)sm);
 
       	pthread_join(tid2, NULL);
	pthread_create(&tid3, NULL, Weather_Condtion, (void *)sm);
	pthread_join(tid3, NULL);

	sem_post(semaphore); // signaling semaphore

	File_Store(sm);
	execl("./p4","p4",NULL,NULL);
}
