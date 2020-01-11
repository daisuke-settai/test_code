bits 64

global _hello

_hello:
  mov rdx, rsi
  mov rsi, rdi
  mov rax, 0x2000004 ; 0x2000000 + 4
  mov rdi, 1
  syscall
  ret

global _my_exit

_my_exit:
  mov rsi, rdi
  mov rax, 0x2000001 ; 0x2000000 + 1
  syscall
