#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char a[4] = "ABC";
  int **ppi;
  int *pia[4]; 
  printf("a[4] = \"ABC\"\n");
  printf("a: %p\n", a);
  printf("&a: %p\n", &a);
  printf("&a[0]: %p, a[0]: %c\n", &a[0], a[0]);
  printf("&a[1]: %p, a[1]: %c\n", &a[1], a[1]);
  printf("&a[2]: %p, a[2]: %c\n", &a[2], a[2]);
  printf("&a[3]: %p, a[3]: %c\n", &a[3], a[3]);
  
  printf("&ppi: %p\n", &ppi);
  printf("malloc(sizeof(int) * 4)\n");
  ppi = (int **)malloc(sizeof(int *) * 4);
  memset((void *)ppi, 0, sizeof(int *) * 4);
  printf("sizeof(ppi): %lu, sizeof(int): %lu\n", sizeof(ppi), sizeof(int *));
  printf("&ppi: %p, ppi: %p\n", &ppi, ppi);
  printf("*ppi: %p, ppi[0]: %p\n", *ppi, ppi[0]);
  printf("&*ppi: %p, &ppi[0]: %p\n", &(*ppi), &ppi[0]);
  printf("*(ppi+1): %p, ppi[1]: %p\n", *(ppi+1), ppi[1]);
  printf("&*(ppi+1): %p, &ppi[1]: %p\n", &(*(ppi+1)), &ppi[1]);
  printf("*(ppi+2): %p, ppi[2]: %p\n", *(ppi+2), ppi[2]);
  printf("&*(ppi+2): %p, &ppi[2]: %p\n", &(*(ppi+2)), &ppi[2]);
  printf("*(ppi+3): %p, ppi[3]: %p\n", *(ppi+3), ppi[3]);
  printf("&*(ppi+3): %p, &ppi[3]: %p\n", &(*(ppi+3)), &ppi[3]);

  printf("sizeof(pia): %lu\n", sizeof(pia));

  return 0;
}
