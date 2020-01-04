#include <stdio.h>

__attribute__((weak)) void f(void) {
  printf("Hi\n");
}
__attribute__((weak, alias("f"))) void g(void);
