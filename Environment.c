#include "headerfile.h"
#include "structure.h"
int Random_Input(unsigned int min ,unsigned int max)
{
       	srand(time(0));
	return rand() %(max -min+1)+min;
}
void Error_Handler(char *message) {
       	perror(message);
}
// Sensor input for Noise
void *Noise_Condition(void *arg) 
{
       	struct scity *sm = (struct scity *)arg;
       	unsigned int Input1;
       	Input1=Random_Input(20,110);
       	sm->e1.noise=Input1;
       	printf("\n:........Noise  Quality Sensed by Noise Senser........:=> %d\n",sm->e1.noise);
       	return NULL;
}
// sensor input for air quality
void *Air_Condition(void *arg) {
       	struct scity *sm = (struct scity *)arg;
       	unsigned int Input2;
       	Input2=Random_Input(0,300);
       	sm->e1.air=Input2;
       	printf("\n:........Air Quality Sensed by Air Senser........:=> %d\n",sm->e1.air);
       	return NULL;
}
// sensor input for weather
void *Weather_Condtion(void *arg) {
       	struct scity *sm = (struct scity *)arg;
       	unsigned int choice ;
       	printf("\n:........Weather Condition Sensor........:=> \n");
       	loop:
       	printf("\nENTER THE CHOICE : 1. Rainy \t : 2. Cloudy : 3. Clear : \n" );
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
	strcpy(sm->e1.weather,"Rainy");
	break;
	case 2:
	strcpy(sm->e1.weather,"Cloudy");
	break;
	case 3:
	strcpy(sm->e1.weather,"Clear");
	break;
	default:
		printf("ENTER PROPER CHOICE\n");
		goto loop;
	}
	return NULL;
}
int main()
{
	printf("\n............Environment Process............\n");
	pthread_t tid1, tid2, tid3;
       	struct scity *sm; // structure pointer
        int shmid;        // shared memory id
        sem_t *semaphore;                        // semaphore pointer
        semaphore = sem_open("/semap1", O_RDWR); // opening semaphore
	if (semaphore == SEM_FAILED)
	{
	       	Error_Handler("semaphore initialization failed");
       	}
       shmid = shmget((key_t)1234, 1024, 0666); // opening shared memory
        if (shmid == -1) 
	{
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
	sleep(5);
	execl("./p4","p4",NULL,NULL);
}
