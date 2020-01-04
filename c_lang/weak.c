#include <stdio.h>
#include "weak_sub.h"

#ifndef STRONG
void f(void) {
  printf("Hello!\n");
}
#endif

__attribute__((constructor)) void begin(void) {
  printf("Start\n");
}

__attribute__((destructor)) void end(void) {
  printf("End\n");
}

int main(void) {
  f();
  g();
  return 0;
}
