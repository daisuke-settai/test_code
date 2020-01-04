target:
	nasm -f elf64 -o hello.o hello.asm
	gcc -O2 -Wall -Wextra hello2.c hello.o -nostdlib -static -Wl,-Map=hello2.map -Wl,-emain 
