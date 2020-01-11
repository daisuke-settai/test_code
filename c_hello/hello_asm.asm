bits 64

global hello

hello:
  mov rdx, rsi
  mov rsi, rdi
  mov rax, 1
  mov rdi, 1
  syscall
  ret

global my_exit

my_exit:
  mov rsi, rdi
  mov rax, 60
  syscall

global _start

_start:
  mov rdi, str_hello
  mov rsi, length
  call hello
  mov rdi, 1
  call my_exit

SECTION .data
  str_hello db "Hello World", 0x0a
  length equ $ - str_hello
