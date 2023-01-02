#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>

#include "Machine/machine.h"

std::vector<unsigned char> readFile(const char *filename) {
  std::ifstream instream(filename, std::ios::in | std::ios::binary);
  std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)),
                            std::istreambuf_iterator<char>());
  return data;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Expected filename arg\n";
    return 0;
  }

  const char *filename = argv[1];
  std::vector<unsigned char> readBytes = readFile(filename);

  Machine machine;
  machine.LoadROM(readBytes);
  machine.Emulate();

  // std::cout << "PROGRAM DUMP:\n";
  // machine.HexDump(0x0100, readBytes.size());
  return 0;
}
