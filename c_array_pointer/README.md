
a: aの値自体はメモリを持たず，コンパイラが処理  	

| addres | var | content | 
| --- | --- | --- |
| 0x7ffeeed5cac8 | a[0], a | A |
| 0x7ffeeed5cac9 | a[1] | B |
| 0x7ffeeed5caca | a[2] | C |
| 0x7ffeeed5cacb | a[3] | \0 |

ppi: ppi 自体がmallocで確保したメモリ領域への値  

| addres | var | content |
| --- | --- | --- |
| 0x7f8e55400620 | *ppi, ppi[0] | 0 |
| 0x7f8e55400628 | *(ppi+1), ppi[1] | 0 |
| 0x7f8e55400630 | *(ppi+2), ppi[2] | 0 |
| 0x7f8e55400638 | *(ppi+3), ppi[3] | 0 |
| ... | ... | ... |
| 0x7ffeeed5cac0 | ppi | 0x7f8e55400620 |

int **ppi : ポインタへのポインタ変数のため sizeof(ppi) => 8 Byte  
int *ppi[4] : ポインタの配列のため sizeof(ppi) => 32 Byte  
