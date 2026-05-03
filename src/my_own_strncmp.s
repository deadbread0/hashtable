global MyOwnStrncmp                      
; nasm -f elf64 -l my_own_strncmp.lst my_own_strncmp.s 

; Аргументы идут в rdi, rsi, rdx, rcx, r8, r9

section .text

;в rdi поступает str1, в rsi - str2

MyOwnStrncmp:   
            call MyOwnStrncmpASM  
            ret                      


;-----------------------------------------------------
; MyOwnStrncmpASM
; enter:    params in stack
; exit:     rax - difference between str
;-----------------------------------------------------
MyOwnStrncmpASM:                          

            xor rax, rax

            vmovups ymm0, [rdi]      ;str1
            vmovups ymm1, [rsi]      ;str2
            vptest  ymm0, ymm1      
            setnb    al

            ret

