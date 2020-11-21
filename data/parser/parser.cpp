#include "data.h"
#include <iostream>

/*
 * ========================================
 * Program to convert a text file into a
 * Skidibidibop Data file (sbbd)
 * ========================================
 */
int main(int argc, char* args[])
{
  if (argc < 2)
  {
    std::cout << "Enter the file you want to convert as the first argument" << std::endl;
    return -1;
  }

  Data::Parser::parse(args[1]);

  return 0;
}
