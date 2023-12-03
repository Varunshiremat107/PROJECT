#include <semaphore.h> 
#include <stdio.h> 
#include <stdlib.h>  
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h> 
#include <fcntl.h>
#include<time.h>
#include "structure.h"

int random_input(int min ,int max)
{
       	srand(time(0));
       	return rand() %(max -min+1)+min;
}

int main() 
{
       	int shmid;
       	int value; 
       	int rem;  
       	
       	printf("\n............Waste Process............\n");

       	sem_t *semaphore; // Semaphore pointer
	semaphore = sem_open("/semap1", O_RDWR); // Create a named semaphore

      	if (semaphore == SEM_FAILED) {
	       	perror("sem_open"); // Error handling
	return 1;
       	}

       	sem_getvalue(semaphore, &value); // Get the value of the semaphore
       	sem_wait(semaphore); // Wait on the semaphore
	sem_getvalue(semaphore, &value); // Get the value of the semaphore

       	shmid = shmget((key_t)1234, sizeof(struct scity),IPC_CREAT | 0666); // Create a shared memory segment

       	if (shmid == -1) {
	       	perror("shmget"); // Error handling
	return 1;
       	}

 
       	struct scity *sm;
       	sm = (struct scity *)shmat(shmid, NULL, 0); // Attach shared memory

       	if (sm == (void *)-1) {
	       	perror("shmat"); // Error handling	
	return 1;
      	}
       	sm->waste = 0; // Initialize waste to 0
       	printf("Enter the number of person adding the waste bin : \n"); 
                                                                 
       	int person;
       	person=random_input(1,5);
       
	for (int i = 0; i < person; i++) {
	       	if (sm->waste <= 100) {
		       	printf("\nCurrent waste in kg: %d\n", sm->waste); 
		       	printf("Remaining limit of the waste in kg to dump : %d\n",(100 - sm->waste));
	       	}
	       
		if (sm->waste >= 100) {
		       	printf("\nWaste is full, cannot dump your %d person waste\n",i + 1); 
		       	break;
	       	}
	       	else {
		       	printf("\nEnter the  waste in kg person : %d \n ",i + 1); 
      			int perwaste;
      			perwaste=random_input(1,100);

			sm->waste = sm->waste + perwaste; // Update waste amount
			rem = sm->waste - 100;
			
			if (sm->waste >= 100) {
        			printf("\nWaste is full, cannot dump %d of kg in your added waste\n",rem); 
        			printf("\nFinal waste in (kg) is : %d\n",sm->waste - rem); 
			}
		}
		sleep(1); 
	}
	if (sm->waste < 100) {
    		printf("\nFinal waste percentage is : %d\n",sm->waste);
	}
	sem_post(semaphore); 
	execl("./p3","p3",NULL,NULL);
}
