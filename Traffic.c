#include "structure.h"
#include "headerfile.h"

int Random_Input(unsigned int min ,unsigned int max)
{
	srand(time(0));
	return rand() %(max -min+1)+min;
	
}
void Error_Handler(char *message)
{
       	perror(message);
}


// Function to capture traffic condition from camera 1

void* Camera1(void *arg)
{	
	unsigned int camera1;
 	struct scity *sm = (struct scity *)arg;
 	camera1=Random_Input(1,100);
 	sm->t1.cam1=camera1;
 	printf("\n:........THE TRAFFIC CONDTION SENSED IN CAMERA 1........:=> %d  \n",sm->t1.cam1);
	return NULL;    	
}


// Function to capture traffic condition from camera 2

void* Camera2(void *arg) {
	int camera2;
  	struct scity *sm = (struct scity *)arg;
  	camera2=Random_Input(20,70);
  	sm->t1.cam2=camera2;
  	printf("\n:........THE TRAFFIC CONDITION SENSED IN CAMERA 2 ........:=> %d  \n",sm->t1.cam2);
  	return NULL;
	
}

// Function to capture traffic condition from camera 3
void* Camera3(void *arg) {
        int camera3;
  	struct scity *sm = (struct scity *)arg;
  	camera3=Random_Input(10,90);
  	sm->t1.cam3=camera3;
 	printf("\n:........THE TRAFFIC CONDITION SENSED IN CAMERA 3........:=>  %d  \n",sm->t1.cam3);
  	return NULL;
	
       	
}


int main() {
 
       	sem_t *semaphore;
        // Opening semaphore
	    semaphore = sem_open("/semap1", O_RDWR);
	    struct scity *sm;
	    int shmid;
	    char str1[10];
	    char str2[10];
	    char str3[10];
	    pthread_t tid1, tid2, tid3;

	    // accesing  shared memory segement
	   shmid = shmget((key_t)1234, sizeof(struct scity), 0666);
	   sm = (struct scity *)shmat(shmid, NULL, 0);
	   sem_wait(semaphore); // Dececreasing the value of semaphore by 1
	   
	   printf("\n:...............Traffic Process...............:\n");

	   // create threads for each camera function and join them to the main thread.
	   pthread_create(&tid1, NULL, Camera1, (void *)sm); // API
           pthread_join(tid1, NULL);
	   pthread_create(&tid2, NULL, Camera2, (void *)sm);
	   pthread_join(tid2, NULL);
	   pthread_create(&tid3, NULL, Camera3, (void *)sm);
	   pthread_join(tid3, NULL);
	 
	   sem_post(semaphore); // Incrementing the value of semaphore by 1
	   sleep(5);
	   execl("./p2","p2",NULL,NULL);
	   
	   
}
