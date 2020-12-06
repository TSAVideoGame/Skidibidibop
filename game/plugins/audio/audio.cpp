#include "audio.h"
#include "sdlw.h"

Game::Plugins::Manager::RegisterPlugin<Game::Plugins::Audio> Game::Plugins::audio_plugin;

// Public members
void Game::Plugins::Audio::play_music(int index)
{
  Mix_PlayMusic(data.musics[index], -1);
}

void Game::Plugins::Audio::pause_music()
{
  Mix_PauseMusic();
}

void Game::Plugins::Audio::stop_music()
{
  Mix_HaltMusic();
}

void Game::Plugins::Audio::play_chunk(int index)
{
  Mix_PlayChannel(-1, data.chunks[index], 0);
}

// Private members
Game::Plugins::Audio::Audio() : Plugin()
{
  SDL_InitSubSystem(SDL_INIT_AUDIO);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  Mix_Volume(-1, volume_max / 4);
}

Game::Plugins::Audio::~Audio()
{
  SDL_QuitSubSystem(SDL_INIT_AUDIO);

  for (Mix_Music* m : data.musics)
    Mix_FreeMusic(m);

  for (Mix_Chunk* c : data.chunks)
    Mix_FreeChunk(c);
}

void Game::Plugins::Audio::reserve_musics(size_t n)
{
  data.musics.reserve(n);
}

void Game::Plugins::Audio::add_music(const std::string& fpath)
{
  data.musics.push_back(Mix_LoadMUS(fpath.c_str()));
}

void Game::Plugins::Audio::reserve_chunks(size_t n)
{
  data.chunks.reserve(n);
}

void Game::Plugins::Audio::add_chunk(const std::string& fpath)
{
  data.chunks.push_back(Mix_LoadWAV(fpath.c_str()));
}
