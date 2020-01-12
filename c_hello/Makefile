linux:
	nasm -f elf64 -o hello_asm.o hello_asm.asm
	gcc -c hello.c -o hello.o
	ld 

linux-hello:
	nasm -f elf64 -o hello_asm.o hello_asm.asm
	ld -o hello_asm hello_asm.o

mac-hello-func:
	nasm -f macho64 hello_asm.asm -o hello_asm.o -DMACOS -DLIB
	gcc -c hello.c -o hello.o
	ld -macosx_version_min 10.13 -lSystem -o hello hello.o hello_asm.o

mac-hello:
	nasm -f macho64 hello_asm.asm -o hello_asm.o -DMACOS
	ld -macosx_version_min 10.13 -lSystem -o hello_asm hello_asm.o -e _start

clean:
	rm -f *.o
	rm -f hello hello_asm
