lda 1
sta $0 ; initialise loop counter at 1 
lda 100
sta $1 ; max 

.main
    call .fizz
    call .buzz

    lda $0xfe
    jne .notdivisible
    lda $0xff
    jne .notdivisible

    lda $0
    int 0x01

    .notdivisible

    lda 0
    sta $0xfe
    sta $0xff

    lda ' '
    int 0x02

    lda $0
    add 1
    sta $0
    cmp $R
    jle .main

.fizz 
    lda $0
    mod 3
    jne .notDivBy3

    lda 'F'
    int 0x02
    lda 'i'
    int 0x02
    lda 'z'
    int 0x02
    lda 'z'
    int 0x02

    lda 1
    sta $0xfe ; $fe = divisible by 3

    .notDivBy3
    ret 0

.buzz 
    lda $0
    mod 5
    jne .notDivBy5

    lda 'B'
    int 0x02
    lda 'u'
    int 0x02
    lda 'z'
    int 0x02
    lda 'z'
    int 0x02

    lda 1
    sta $0xff ; $ff = divisible by 5

    .notDivBy5
    ret 0