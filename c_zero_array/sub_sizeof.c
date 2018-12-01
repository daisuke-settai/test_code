#include <stdio.h>
#include <stdlib.h>

int main ()
{
  int ans;
  ans = (int)&(((int*)0)[1]);
  printf("int size: %d\n", ans);
  printf("int size: %d\n", sizeof(ans));

  return 0;
}

