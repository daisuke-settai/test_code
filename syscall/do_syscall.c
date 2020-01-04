#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

int main(void){
  syscall(1, 1, "hello\n", 6);
  return 0;
}
