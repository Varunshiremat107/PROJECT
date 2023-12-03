#include"headerfile.h"
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


       	struct scity var;
        struct scity *sm = &var;
        sm = (struct scity *)shmat(shmid, NULL, 0); // Attach shared memory
       
      	if (sm == (void *)-1) {
	       	perror("shmat"); // Error handling
	       	return 1;
       	}

	int rem;
	sm->waste = random_input(0, 10);
	printf("current waste = %d\n", sm->waste);
	printf("remaining %d\n", (100 - sm->waste));
	int person;
	person = random_input(1, 5);
	printf("number of person adding the waste bin : %d\n", person);

	for (int i = 0; i < person; i++) {
		if (sm->waste <= 100) {
			printf("\nCurrent waste in kg: %d\n", sm->waste);
			printf("Remaining limit of the waste in kg: %d\n", (100 - sm->waste));
		}

		if (sm->waste >= 100) {
			printf("Bin is full. Cannot dump any more waste\n");
			break;
		}
	       	else {
			int perwaste;
			perwaste = random_input(1, 100);
			printf("added %d\n", perwaste);
			rem = 100 - sm->waste;
			printf("rem = %d\n", rem);

			if ((perwaste + sm->waste) >= 100) {
				sm->waste = sm->waste + rem;
				printf("current = %d\n", sm->waste);
				break;
			}

			if ((perwaste + sm->waste) < 100)
				sm->waste = sm->waste + perwaste;
				printf("current = %d\n", sm->waste);
		}
		sleep(1);
	}

	if (sm->waste < 100) {
		printf("Final waste percentage is : %d\n", sm->waste);
	}
      	sem_post(semaphore); 
       	sleep(5);

       	execl("./p3","p3",NULL,NULL);
}
