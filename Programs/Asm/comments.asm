.loop
    lda $0
    add 1; loop increment counter

    int 0x01
    sta $0 ;store and compare values
    cmp 10
    jl .loop