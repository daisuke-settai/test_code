bits 64

%ifdef MACOS
  %define SYS_WRITE   0x2000004
  %define SYS_EXIT    0x2000001
  %define hello_func  _hello
  %define exit_func   _my_exit
%else
  %define SYS_WRITE   1
  %define SYS_EXIT    60
  %define hello_func  hello
  %define exit_func   my_exit
%endif

global hello_func

hello_func:
  mov rdx, rsi
  mov rsi, rdi
  mov rax, SYS_WRITE
  mov rdi, 1
  syscall
  ret

global exit_func

exit_func:
  mov rsi, rdi
  mov rax, SYS_EXIT
  syscall

%ifndef LIB
  global _start

  _start:
    mov rdi, str_hello
    mov rsi, length
    call hello_func
    mov rdi, 1
    call exit_func

  SECTION .data
    str_hello db "Hello World", 0x0a
    length equ $ - str_hello
%endif
