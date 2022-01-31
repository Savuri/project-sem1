section .data
    p1 dq 2.0
    p2 dq 6.0
    p3 dq 14.0   
    
section .bss
    c resq 1
section .text
extern log
global f1
f1:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 12]
    push eax
    mov eax, [ebp + 8]
    push eax
    call log
    mov esp, ebp
    pop ebp
    ret

global f2
f2:
    push ebp
    mov ebp, esp
    sub esp, 12
    
    finit
    fldz
    fld qword[p1]
    fsubp
    fld qword[ebp + 8]
    fmulp
    fld qword[p3]
    faddp
    
    
    
    
    mov esp, ebp
    pop ebp
    ret

global f3
f3:
    push ebp
    mov ebp, esp
    
    finit
    fld1
    fld qword[p1]
    fld qword[ebp + 8]
    fsubp
    fdivp
    fld qword[p2]
    faddp
    
    

    
    
    mov esp, ebp
    pop ebp
    ret

global df1
df1:
    push ebp
    mov ebp, esp
    
    finit
    fld1
    fld qword[ebp + 8]
    fdivp

    
    mov esp, ebp
    pop ebp
    ret

global df2
df2:
    push ebp
    mov ebp, esp
    
    finit
    fldz
    fld qword[p1]
    fsubp
    

    
    mov esp, ebp
    pop ebp
    ret

global df3
df3:

    push ebp
    mov ebp, esp
    
    finit
    fld1
    fld qword[p1]
    fld qword[ebp + 8]
    fsubp
    fdivp
    fld qword[p1]
    fld qword[ebp + 8]
    fsubp
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
