void hello(char *string, int len);
void my_exit(int) __attribute__((noreturn));

int main(int argc, char *argv[]){
  char *string = "Hello Asm!\n";
  hello(string, __builtin_strlen(string));
  hello(argv[0], 6);
  my_exit(0);
}
