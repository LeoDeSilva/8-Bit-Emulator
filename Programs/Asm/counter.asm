lda 1
sta $0 ; initialise loop counter at 1 

.startLoop
    lda $0
    int 0x01
    lda ' '
    int 0x02

    lda $0
    add 1
    sta $0
    cmp 10
    jle .startLoop
    jmp .end

.end 
    lda 'D'
    int 0x02
    lda 'o'
    int 0x02
    lda 'n'
    int 0x02
    lda 'e'
    int 0x02
    lda '!'
    int 0x02