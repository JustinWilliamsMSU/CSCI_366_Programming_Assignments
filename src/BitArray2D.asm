
        global  set_bit_elem
        global  get_bit_elem
        section .text

set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here

    ; =======================================
    ; Calculate index of current array addr
        ; index = row*row_width + column                CHECK
        ; byte_offset = index / 8                       CHECK
        ; bit_offset = index - (byte_offset * 8)
        ; mask = 1 << (8 - bit_offset)
        ; byte := byte or mask
    ; =======================================
        ; Example Hardcode
        mov  rdx, 2
        mov  rcx, 1

        mov  rax, rsi           ; Moves row_width to rax register
        imul rax, rdx           ; Multiplies row_width * row
        add  rax, rcx           ; Adds column to row_width * row

        mov  rbx, rax           ; Store index to another variable (use it later)
        sar  rbx, 3             ; BYTE_OFFSET  Divides index by 8
        sal  rbx, 3             ; Multiply byte_offset * 8
        sub  rax, rbx           ; BIT_OFFSET    index - byte_offset*8

        mov  rbx, 1 << rax ; DOES NOT WORK \\ RAX = 7
        mov  rbx, 1 << 7   ; DOES WORK

    ; =======================================
    ; Set bit in memory if it's a 1
    ; =======================================
        mov rax, [rdi]
        or  rax, 1





        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax




get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here - for now returning 0
   ; =======================================
    ; compare row with row width
    ; if (row >= row_width) {
    ;    move to next row
    ; } else {
    ;    add rdi to current row
    ; }
    ; =======================================


        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
