#include "headerfile.h"
#include "structure.h"
int random_input(int min, int max)
{
	srand(time(0));
	return rand() % (max - min + 1) + min;
}
int main()
{
	int shmid;
	int value;
	printf("\n............Waste Process............\n");
	sem_t *semaphore;                        // Semaphore pointer
	semaphore = sem_open("/semap1", O_RDWR); // Open a named semaphore
	if (semaphore == SEM_FAILED) 
	{
		perror("sem_open"); // Error handling
		return 1;
	}
	sem_wait(semaphore);                     // Wait on the semaphore
	shmid = shmget((key_t)1234, sizeof(struct scity),IPC_CREAT | 0666);        // Create a shared memory segment
	if (shmid == -1)
	{
		perror("shmget");                     // Error handling
		return 1;
	}
	struct scity var;
	struct scity *sm = &var;
	sm = (struct scity *)shmat(shmid, NULL, 0); // Attach shared memory
	if (sm == (void *)-1)
	{
		perror("shmat");                     // Error handling
		return 1;
	}
	int rem;
	sm->waste = random_input(0, 10);
	printf("\n CURRENT WASTE IN THE BIN = %d KG\n", sm->waste);
	printf(" REMAINING LIMIT IN THE BIN : %d KG\n", (100 - sm->waste));
	int person;
	person = random_input(1, 5);
	printf(" NUMBER OF PERSON ADDING TO THE BIN : %d\n", person);
	for (int i = 0; i < person; i++) {
	if (sm->waste <= 100)
	{
	printf("\nCURRENT WASTE: %d KG\n", sm->waste);
	printf("REMAINING LIMIT IN THE BIN: %d KG\n", (100 - sm->waste));
	}
	if (sm->waste >= 100)
	{
		printf("BIN IS FULL. CAN'T DUMP YOUR WASTE\n");
		break;

        }
	else
	{
		int perwaste;
		perwaste = random_input(1, 100);
		printf("WASTE ADDED IN THE BIN =%d KG\n", perwaste);
		rem = 100 - sm->waste;
		if ((perwaste + sm->waste) >= 100)
		{
			sm->waste = sm->waste + rem;
			printf("  CURRENT WASTE IN BIN = %d KG\n", sm->waste);
			break;

            	}
		if ((perwaste + sm->waste) < 100)
		{
			sm->waste = sm->waste + perwaste;
			printf("CURRENT WASTE IN BIN = %d KG\n", sm->waste);
		}
		sleep(1);
	}
		if (sm->waste < 100)
		{
			printf("\n FINAL WASTE COLLETION IN BIN : %d KG\n", sm->waste);
		}
		sem_post(semaphore);
		sleep(5);
		execl("./p3", "p3", NULL, NULL);
	}
}
