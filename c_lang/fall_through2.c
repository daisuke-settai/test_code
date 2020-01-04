__attribute((section(".text"))) int main = 0x90909090;
void f1() { puts("world!"); }
__attribute((constructor)) void f2() { puts("hello"); }

