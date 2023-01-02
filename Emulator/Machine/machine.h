#pragma once
#include <cstdint>
#include <vector>

#define SYS_MEMORY 0x0000
#define PROG_MEMORY 0x0100
#define FREE_MEMORY 0x4001

#define HLT 0x00
#define CALL 0x10
#define RET 0x11

#define JMP 0x20
#define JNE 0x21
#define JG 0x22
#define JGE 0x23
#define JL 0x24
#define JLE 0x25
#define JE 0x26

#define LDA 0x30
#define STA 0x40

#define ADD 0x50
#define SUB 0x51
#define MUL 0x52
#define DIV 0x53
#define MOD 0x54

#define CMP 0x60
#define INT 0x70

class Machine
{
public:
  void LoadROM(std::vector<unsigned char>);
  void Emulate();
  void Dump(int, int);
  void HexDump(int, int);

  Machine()
  {
    v.resize(0x100);
    memory.resize(0xffff);
    stack.resize(16);
    buffer.resize(64 * 32); // screen dimensions

    for (int i = 0; i < memory.size(); i++)
      memory.at(i) = 0;

    for (int i = 0; i < v.size(); i++)
      v.at(i) = 0;
  }

private:
  std::uint16_t PC;
  std::uint16_t SP;
  std::uint16_t MAR;
  std::uint8_t ACC;

  std::vector<std::uint8_t> v; // register V0 -> V255
  std::vector<std::uint8_t> memory;
  std::vector<std::uint8_t> buffer; // display buffer
  std::vector<std::uint16_t> stack;

  bool hlt;

  void EmulateCycle();
  uint16_t FetchOperand(uint8_t, uint16_t);
};
