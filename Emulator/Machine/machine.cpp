#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "machine.h"

void Machine::HexDump(int start, int size)
{
  for (int loc = 0; loc < size; ++loc)
  {
    std::ostringstream ss;
    ss << std::hex << (int)memory.at(start + loc);
    std::string result = ss.str();

    if (result.length() == 1)
      std::cout << "0" << result << " ";
    else
      std::cout << result << " ";
  }

  std::cout << std::endl;
}

void Machine::Dump(int start, int size)
{
  for (int loc = 0; loc < size; ++loc)
  {
    std::cout << std::bitset<8>(memory.at(start + loc)).to_string() << " ";
  }

  std::cout << "\n";
}

void Machine::LoadROM(std::vector<unsigned char> program)
{
  for (int loc = 0; loc < program.size(); ++loc)
  {
    memory.at(PROG_MEMORY + loc) = program[loc];
  }

  PC = PROG_MEMORY;
}

uint16_t Machine::FetchOperand(uint8_t reference, uint16_t operand)
{
  // ignoring implementation of negatives
  switch (reference & 0xF0)
  { // ignore neg? when deciding addressing mode
  case 0x10:
    return v.at(operand);

  case 0x20:
    return memory.at(operand);

  default:
    return operand;
  }
}

void Machine::Emulate()
{
  while (!hlt)
  {
    EmulateCycle();
  }
}

void Machine::EmulateCycle()
{
  // HexDump(PC, 4);
  uint8_t opcode = memory.at(PC);
  uint8_t referenceLiteral = memory.at(PC + 1); // addressing mode + neg?
  uint16_t operandLiteral =
      (memory.at(PC + 2) << 8) |
      memory.at(PC + 3); // pure value for specific handling (e.g. jmp)
  unsigned int instruction = (memory.at(PC) << 24) | (memory.at(PC + 1) << 16) |
                             (memory.at(PC + 2) << 8) | memory.at(PC + 3);

  uint16_t operand = FetchOperand(
      referenceLiteral, operandLiteral); // Numerical value (extracted from mem)

  PC += 4;

  switch (opcode)
  {
  case HLT:
    hlt = true;
    break;

  case CALL:
    stack.push_back(PC);
    // for (int index : stack)
    //   std::cout << index << std::endl;

    PC = operand;
    break;

  case RET:
    PC = stack[stack.size() - 1];
    stack.erase(stack.end() - 1);
    break;

  case JMP:
    PC = operand;
    break;

  case JE:
    if (ACC == 0)
      PC = operand;
    break;
  case JNE:
    if (ACC != 0)
      PC = operand;
    break;
  case JG:
    if (ACC == 2)
      PC = operand;
    break;
  case JGE:
    if (ACC == 0 || ACC == 2)
      PC = operand;
    break;
  case JL:
    if (ACC == 1)
      PC = operand;
    break;
  case JLE:
    if (ACC == 0 || ACC == 1)
      PC = operand;
    break;

  case LDA:
    ACC = operand;
    break;

  case STA:
    switch (referenceLiteral)
    {
    case 0x10:
      v.at(operandLiteral) = ACC;
      break;

    case 0x20:
      memory.at(operandLiteral) = ACC;
      break;

    default:
      hlt = true;
      std::cout
          << std::hex << instruction
          << ": SEGMENTATION FAULT: Cannot reference 'integer' as address\n";
    }
    break;

  case ADD:
    ACC += operand;
    break;

  case SUB:
    ACC -= operand;
    break;

  case MUL:
    ACC *= operand;
    break;

  case DIV:
    ACC /= operand;
    break;

  case MOD:
    ACC %= operand;
    break;

  case CMP:
    if (ACC - operand > 0) // > = 2
      ACC = 2;
    else if (ACC - operand < 0) // < = 1
      ACC = 1;
    else // == = 0
      ACC = 0;

    break;

  case INT:
    switch (operand)
    {
    case 0x00: // DRAW
      break;

    case 0x01: // OUT
      std::cout << (int)ACC;
      break;

    case 0x02: // OUT
      std::cout << ACC;
      break;

    case 0x03: // IN
      break;
    }
  }

  return;
}
