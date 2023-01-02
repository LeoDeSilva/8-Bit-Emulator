# Readme
An Emulator for an original 8-bit computer running assembly instructions with similar syntax to intel x86 (notealy simpler). Repository contains both the Emulator and Assembler to compile and run programs. 

Below is an example fizz-buzz program, executed with the command (inside the Emulator directory) `./main ../Programs/Bin/fizz.bin`. The language makes heavy use of the ACC as an intermediary between operations. Thus programs are notably larger than otherwise, yet... it saved a lot of time in implementation, so ¨\_( ._.)_/¨

```assembly
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
```

Scaffolding Transpiler for more complex instructions:
```assembly
msg 'Hi', $0x4000
    ; lda 'H'
    ; sta $0x4000
    ; lda 'i'
    ; sta $0x4001

mov (a), (b) -> lda (a); sta (b)
mov 10, $ff
    ; lda 10
    ; sta $ff

mov %ff, $ee
    ; lda %ff
    ; sta $ee

mov 10, 10
    ; err

lda (b) -> add (a) -> ¿sta(b)?
add 10, 0x02
    ; lda 0x02
    ; add 10
    ; no register/mem -> leave in ACC
add 10, %0
    ; lda %0
    ; add 10
    ; sta %0
add $0, %10
    ; lda %10
    ; add $0
    ; sta %10
add $0, 10
    ; lda 10
    ; add $10
    ; (no store since number)


msg 'Hello World', %0x4000
mov 0x4000, $0xfe
mov 11, $0xff
int 0x03 ; display string

mov 10, $10
; lda 10
; sta $10

out
; int 0x01
print 'h'
; lda 104
; int 0x02

call .helloWorld

.helloWorld
    print 'h'
    print 'i'
    print '!'
    ret

```
