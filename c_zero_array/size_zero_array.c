#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

struct zero_struct 
{
  int body[0];
};

int main()
{ 
  struct zero_struct z;
  struct zero_struct *zp;
  int i;
  
  printf("int size : %d\n", sizeof(i));

  printf("struct size : %d\n", sizeof(z));
  zp = (struct zero_struct *)malloc(sizeof(int) * ARRAY_SIZE);
  
  for (i = 0; i < ARRAY_SIZE; i++){
    zp->body[i] = 0;
  }

  printf("struct pointer size : %lu\n", sizeof(zp));  
  printf("address: %p\n", zp);
  printf("array size : %d\n", sizeof(*zp));  
  printf("exited successfully\n");
  return 0;
}

