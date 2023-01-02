mov 1, $0
; lda 1
; sta $0

.fizzbuzz
lda $0
int 0x01 ; int out
add 1, $0
; lda $0
; add 1
; (sta $0)
cmp 10
jl .fizzbuzz