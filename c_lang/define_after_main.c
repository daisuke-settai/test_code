#include <stdio.h>

#ifndef INCLUDED
#define INCLUDED
#include __FILE__

int main(void)
{
    hello(); // OK
}
#else
void hello(void)
{
    puts("Hello World!");
}
#endif
