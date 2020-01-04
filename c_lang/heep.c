#include <stdio.h>

__attribute__((constructor)) void dump_maps() {
  FILE* fp;
  int c;
  fp = fopen("/proc/self/maps", "rb");
  while((c = fgetc(fp)) != EOF) {
    putchar(c);
  }
  fclose(fp);
}

int main(){
  int i;
  int(*f[10])();
  for(i = 0; i < 10; i++) {
    int a() { return i; }
# ifdef STACK_EXEC
    f[i] = &a;
#endif
  }
  return 0;
}
