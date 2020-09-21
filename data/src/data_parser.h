#ifndef TSA_GAME_DATA_PARSER
#define TSA_GAME_DATA_PARSER

#include <string>
#include <variant>

namespace Data
{
  /*
   * ========================================
   * Map::Parser
   *
   * Tools for parsing a map text file and
   * converting it into a binary file
   *
   * The tokenizer and parser are both in this
   * class
   * ========================================
   */
  class Parser
  {
  public:
    static int Parse(const std::string& fpath); // Parses text data into map data
  private:
    Parser() {} // Class cannot be instantiated
    // Tokenizer / Lexical Analysis
    struct Token
    {
      enum class Type {PROPERTY, COLLECTION_OPEN, COLLECTION_CLOSE, U_INT, BOOL};
      Type type;
      void* data = nullptr;
      size_t size;

      ~Token()
      {
        if (data != nullptr)
          free(data);
      }
    };
    static Token* makeTokenData(const std::string& data);
    // Parser
    struct Data
    {
      enum class Type {COLLECTION, U_INT, BOOL};

    };
  };
};

#endif
