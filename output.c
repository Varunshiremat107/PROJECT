#include "headerfile.h"
#define FILENAME "file.txt"
// declaring structure variable
struct mq 
{
  char b1[7][100];
};
int main()
{
  FILE *file = fopen(FILENAME, "a");
  if (file == NULL)
  {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
int msgid;
char buff1[50];
struct mq data;
printf("\n---------------------------------------------------\n");
// loop to print messages from message-Queue
for (int i = 0; i < 7; i++) 
{
    msgid = msgget((key_t)17834, 0666 | IPC_CREAT);
    msgrcv(msgid, &data, sizeof(data.b1), 0, 0);
    printf("\n%s\n", data.b1[i]);
    fprintf(file, "%s\n", data.b1[i]);
  }
  printf("\n---------------------------------------------------\n");
  fclose(file);
}
