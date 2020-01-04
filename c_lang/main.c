#include <unistd.h>

__attribute__((constructor, destructor)) int main() {
  static int i = 0;
  if (i) i += write(1, "world!\n", 7);
  else i = write(1, "hello ", 6);
}
