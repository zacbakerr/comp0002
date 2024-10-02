// Written by Zachary Baker, 01/10/24
// This program displays my name

#include <stdio.h>
#include <string.h>

int main(void) {
  char myName[] = "Zachary Baker";
  printf("Hello! My name is %s\n", myName);
  
  int index = strlen(myName) - 1;
  while (index > -1) {
    printf("%c", myName[index]);
    index--;
  }
  printf("\n");
  return 0;
}