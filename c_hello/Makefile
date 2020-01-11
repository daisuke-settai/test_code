linux:
	nasm -f elf64 -o hello.o hello.asm
	gcc -O2 -Wall -Wextra hello2.c hello.o -nostdlib -static -Wl,-Map=hello2.map -Wl,-emain -o hello

mac-hello-func:
	nasm -f macho64 mac_hello_asm_func.asm -o mac_hello_asm_func.o
	gcc -c hello2.c -o hello2.o
	ld -macosx_version_min 10.13 -lSystem -o mac_hello_asm_func hello2.o mac_hello_asm_func.o

mac-hello:
	nasm -f macho64 mac_hello_asm.asm -o mac_hello_asm.o
	ld -macosx_version_min 10.13 -lSystem -o mac_hello_asm mac_hello_asm.o

clean:
	rm -f *.o
