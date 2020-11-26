#ifndef SKIDIBIDIBOP_GAME_PLUGINS_AUDIO
#define SKIDIBIDIBOP_GAME_PLUGINS_AUDIO

#include "plugin.h"
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

namespace Game
{
  namespace Plugins
  {
    // This trick here prevents Game::Core from accessing these members
    struct AudioData
    {
    private:
      std::vector<Mix_Music*> musics;
      std::vector<Mix_Chunk*> chunks;

      friend class Audio;
    };

    class Audio : public Plugin
    {
    public:
      static const int volume_max = MIX_MAX_VOLUME;
      static const int volume_min = 0;

      void play_music(int);
      void pause_music();
      void stop_music();

      void play_chunk(int);

      void set_music_volume(int volume);
    private:
      Audio();
      ~Audio();

      void reserve_musics(size_t);
      void add_music(const std::string& fpath);
      void reserve_chunks(size_t);
      void add_chunk(const std::string& fpath);

      AudioData data;

      friend class Game::Core;
    };
  };
};

#endif
