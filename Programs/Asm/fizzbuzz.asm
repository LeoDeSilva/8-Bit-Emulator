lda 1
sta $0
lda $0
mod 3
jne @5
lda 70
int 0x02
lda 1
sta $3
lda $0
mod 5
jne @5
lda 66
int 0x02
lda 1
sta $5
lda $5 
jne @5
lda $3
jne @3
lda $0
int 0x01
lda 32
int 0x02
lda 0
sta $3
sta $5
lda $0
add 1
sta $0
cmp 100
jl @-29