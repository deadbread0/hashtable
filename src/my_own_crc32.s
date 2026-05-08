; nasm -f elf64 -l my_own_crc32.lst my_own_crc32.s
;rdi - word

global CRC32ASM
section .text

CRC32ASM:
    mov rax, -1    

    crcloop:
    mov cl, [rdi]    
    crc32 rax, cl           
    inc rdi  
    cmp cl, 0              
    jne crcloop                

    ret  