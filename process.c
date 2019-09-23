#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  //int seconds = (int) atoi(argv[0]);
  printf("Child: Sleeping for %s seconds\n", argv[0]);
  sleep((int)atoi(argv[0]));
  printf("Child: Done sleeping. Attempting to go back to parent process.\n");
  //exit(0);
}