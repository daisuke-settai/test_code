bits 64

%ifdef MACOS
  %define SYS_WRITE 0x2000004
  %define SYS_EXIT  0x2000001
%else
  %define SYS_WRITE 1
  %define SYS_EXIT  60
%endif

global _hello

_hello:
  mov rdx, rsi
  mov rsi, rdi
  mov rax, SYS_WRITE
  mov rdi, 1
  syscall
  ret

global _my_exit

_my_exit:
  mov rsi, rdi
  mov rax, SYS_EXIT
  syscall

%ifndef LIB
  global _start

  _start:
    mov rdi, str_hello
    mov rsi, length
    call _hello
    mov rdi, 1
    call _my_exit

  SECTION .data
    str_hello db "Hello World", 0x0a
    length equ $ - str_hello
%endif
