#include "data_parser.h"

#include <iostream>
#include <fstream>
#include <deque>
#include <cstring>

/*
 * ========================================
 * Data::Parser::Parse
 *
 * Parses text data and outputs a binary file the game can use
 * The memory handling isn't the cleanest, but it works
 *
 * Returns:
 * int | Success code
 *
 * Parameters:
 * const std::string& fpath | The file location
 * ========================================
 */

int Data::Parser::Parse(const std::string& fpath)
{
  std::ifstream textFile;
  textFile.open(fpath);

  // File needs to exist
  if (!textFile.is_open())
  {
    std::cout << "ERROR::Map::Parser::Parse::FILE_NOT_FOUND " << fpath << std::endl; // Should probably make a logger class
    return -1;
  }

  // Tokenizer / Lexical Analysis
  std::deque<Token*> tokens;
  char currentChar;
  Token::Type currentType;
  std::string currentData;

  while (!textFile.eof())
  {
    currentChar = textFile.get();
    if (currentChar == '@') // Property
    {
      if (currentData.compare(""))
        tokens.push_back(makeTokenData(currentData));
      currentData = "";

      currentChar = textFile.get();
      while (currentChar != '\n')
      {
        currentData += currentChar;
        currentChar = textFile.get();
      }

      Token* t = new Token();
      t->type = Token::Type::PROPERTY;
      t->data = malloc(currentData.length());
      std::memcpy(t->data, reinterpret_cast<const void*>(currentData.c_str()), currentData.length());
      t->size = currentData.length();
      tokens.push_back(t);

      currentData = "";
    }
    else if (currentChar == ' ' || currentChar == '\n' || currentChar == '\0') // Whitespace
    {
    }
    else if (currentChar == '#') // Comment
    {
      while (currentChar != '\n')
        currentChar = textFile.get();
    }
    else if (currentChar == '[') // Open Collection
    {
      Token* t = new Token();
      t->type = Token::Type::COLLECTION_OPEN;
      t->size = 0;
      tokens.push_back(t);
    }
    else if (currentChar == ']') // Close Collection
    {
      if (currentData.compare(""))
        tokens.push_back(makeTokenData(currentData));
      currentData = "";

      Token* t = new Token();
      t->type = Token::Type::COLLECTION_CLOSE;
      t->size = 0;
      tokens.push_back(t);
    }
    else if (currentChar == ',')
    {
      if (currentData.compare(""))
        tokens.push_back(makeTokenData(currentData));
      currentData = "";
    }
    else // Any non-reserved characters will be put into data
    {
      currentData += currentChar; // This adds the EOF file but whatever, it doesn't tokenize that 
    }
  }

  /*
   * There will be no parser and no WDYM until I
   * have time for a side project, meanwhile all
   * the data will just get convered to binary.
   */
  std::ofstream dataFile(fpath.substr(0, fpath.length() - 3) + "sbbd", std::ios::trunc | std::ios::binary);
  for (Token* t : tokens)
  {
    switch (t->type)
    {
      case Token::Type::U_INT:
      {
        dataFile.write(reinterpret_cast<char*>(t->data), sizeof(unsigned int));
        break;
      }
      case Token::Type::BOOL:
      {
        dataFile.write(reinterpret_cast<char*>(t->data), sizeof(bool));
        break;
      }
      default:
      {
        break;
      }
    }
  }
  
  // Free up memory
  for (Token* t : tokens)
    delete t;

  return 0;
}

Data::Parser::Token* Data::Parser::makeTokenData(const std::string& data)
{
  //std::cout << "Current data is: " << data << " Length: " << data.length() << std::endl;
  Token* t = new Token();

  if (data.compare(""))
  {
    if (!data.compare("t") || !data.compare("f")) // Boolean
    {
      t->type = Token::Type::BOOL;
      t->data = malloc(sizeof(bool));
      t->size = sizeof(bool);
      if (!data.compare("t"))
        *(reinterpret_cast<bool*>(t->data)) = true;
      else
        *(reinterpret_cast<bool*>(t->data)) = false;
    }
    else // For now only boolean and unsigned integers are supported
    {
      t->type = Token::Type::U_INT;
      t->data = malloc(sizeof(unsigned int));
      t->size = sizeof(unsigned int);

      try
      {
        *(reinterpret_cast<unsigned int*>(t->data)) = std::stoul(data);
      }
      catch (std::invalid_argument e)
      {
        std::cout << "ERROR::Map::Parser::makeTokenData::INVALID_UNSIGNED_INTEGER " << data << std::endl;
        *(reinterpret_cast<unsigned int*>(t->data)) = 0;
      }
    }
  }

  return t;
}
