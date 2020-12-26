#ifndef SKIDIBIDIBOP_GAME_LOGGER
#define SKIDIBIDIBOP_GAME_LOGGER

#include <string>
#include <fstream>
#include <cstdint>

namespace Game
{
  /*
   * ========================================
   * Logger
   *
   * Logs to a file
   * ========================================
   */
  class Logger
  {
  public:
    /*
     * ========================================
     * Logger::Code
     *
     * Code of the log, supports 8 slots
     * ========================================
     */
    enum Code 
    {
      LOG    = 1 << 0,
      ERROR  = 1 << 1,
      SLOT_3 = 1 << 2,
      SLOT_4 = 1 << 3,
      SLOT_5 = 1 << 4,
      SLOT_6 = 1 << 5,
      SLOT_7 = 1 << 6,
      SLOT_8 = 1 << 7
    };

    Logger(const std::string&);
    ~Logger();

    void log(std::uint8_t, const std::string&);
    void enable(std::uint8_t);
    void disable(std::uint8_t);
  private:
    std::ofstream file;
    std::uint8_t code;

    static const char * const code_names[8];
  };
};

#endif
