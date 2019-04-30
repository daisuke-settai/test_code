int main() {
    asm("mov rax, 1");
    asm("mov rdi, 1");
    asm("mov rbx, 0x0a434241");
    asm("push rbx");
    asm("mov rsi, rsp");
    asm("mov rdx, 4");
    asm("syscall");

    return 0;
}
