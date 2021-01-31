#include "logger.h"

const char * const Game::Logger::code_names[8] = {
  "LOG",
  "ERROR",
  "DEBUG",
  "",
  "",
  "",
  "",
  ""
};

Game::Logger::Logger(const std::string& fpath)
{
  file_path = fpath;
  code = 0;

  std::ofstream file(file_path, std::ofstream::trunc);
  file.close();
}

Game::Logger::~Logger()
{

}

/*
 * ========================================
 * Log
 *
 * Logs a message with a code, will log the
 * code with the lowest slot
 * ========================================
 */
void Game::Logger::log(std::uint8_t c, const std::string& msg)
{
  if (c | code)
  {
    std::ofstream file(file_path);

    std::uint8_t a = 1;
    int position = 0;

    // Shifts a until a number finally works
    while (!(c & a))
    {
      a <<= 1;
      ++position;
    }

    file << code_names[position] << ": " << msg << "\n";

    file.close();
  }
}

void Game::Logger::enable(std::uint8_t c)
{
  // Just OR will work
  code |= c;
}

void Game::Logger::disable(std::uint8_t c)
{
  // AND the inverse of c
  code &= ~c;
}
