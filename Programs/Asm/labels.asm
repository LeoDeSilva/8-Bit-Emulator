lda 1
sta $0
.loop
  lda $0
  add 1
  sta $0

  int 0x01

  cmp 10
  jl .loop
