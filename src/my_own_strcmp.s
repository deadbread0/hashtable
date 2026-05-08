global MyOwnStrcmp                      
; nasm -f elf64 -l my_own_strcmp.lst my_own_strcmp.s 

; Аргументы идут в rdi, rsi, rdx, rcx, r8, r9

section .text

;в rdi поступает str1, в rsi - str2

MyOwnStrcmp:   
            call MyOwnStrcmpASM  
            ret                      


;-----------------------------------------------------
; MyOwnStrcmpASM
; enter:    params in stack
; exit:     rax - difference between str
;-----------------------------------------------------
MyOwnStrcmpASM:                          

            xor rax, rax

            vmovups ymm0, [rdi]      ;str1
            vmovups ymm1, [rsi]      ;str2
            vptest  ymm0, ymm1      
            setnb    al

            ret

