# Readme

Compiler:

```
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
