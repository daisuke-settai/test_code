#include <stdio.h>

int main(){
  int xxx = 100;
  int a[1000000];
  int i = 0;
  getchar();
  while(1){
    printf("%d: %p, %d\n", i, &a[i], a[i]);
    i++;
  }

  return 0;
}
