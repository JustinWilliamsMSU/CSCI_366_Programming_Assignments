
        global  set_bit_elem
        global  get_bit_elem
        section .text

set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame
        ; REGISTER INFORMATION
        ;=======================================
        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col
        ;=======================================

        ;=======================================
        ; Calculate index of current array addr
            ; index = row*row_width + column                CHECK
            ; byte_offset = index / 8                       CHECK
            ; bit_offset = index - (byte_offset * 8)
            ; mask = 1 << (8 - bit_offset)
            ; byte := byte or mask
        ;=======================================

        mov  rax, rsi           ; Moves row_width to rax register
        imul rax, rdx           ; Multiplies row_width * row
        add  rax, rcx           ; Adds column to row_width * row

        mov  rbx, rax           ; Store index to another variable (use it later)
        sar  rbx, 3             ; BYTE_OFFSET  Divides index by 8
        sal  rbx, 3             ; Multiply byte_offset * 8
        sub  rax, rbx           ; BIT_OFFSET    index - byte_offset*8

        ; Calculate mask
        mov  rbx, 8
        sub  rbx, rax           ; SHIFT_AMNT = 8 - BIT_OFFSET
        dec  rbx                ; SHIFT_AMNT = SHIFT_AMNT - 1

        mov  rsi, 0             ; SHIFT COMPARE VARIABLE, INC UNTIL = RBX
        mov  rax, 1             ; MASK VALUE (TO BE SHIFTED) UNTIL RSI == RBX
        compare_shift:
            cmp  rbx, rsi
            je   done           ; If Equal, jump to done, else, shift left
        shift_left:
            sal rax, 1
            inc rsi
            jmp compare_shift
        done:

            imul rdx, 10
            add rdx, rcx
            sar rdx, 3
            mov rbx, [rdi+rdx]
            or  rbx, rax
            mov [rdi+rdx], rbx
            mov rax, rbx
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
        mov rax, rdx    ;move row into rax
        imul rax, rsi   ;multiple row by row width
        add rax, rcx    ;add columns        ;index on where i am in array, rdi + rax
        sar rax, 3
        mov rax, [rdi + rax]

        ;add rdi, rax
        ;mov rax, [rdi]
        cmp rax, 0
        setg al
        movsx rax, al



        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
