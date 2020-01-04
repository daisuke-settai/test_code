void hello(char *string, int len);
void my_exit(int) __attribute__((noreturn));

int main(){
  char *string = "Hello Asm!\n";
  hello(string, __builtin_strlen(string));
  my_exit(0);
}
