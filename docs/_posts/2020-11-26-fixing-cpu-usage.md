---
layout: post
title: "Fixing CPU Usage"
date: 2020-11-26 19:03 -0500
author: mjir
categories: engine
---

After noticing how loud my computer was getting after running the map editor (along with other problems like the map editor just
causing one of our member's computers to freeze), I noticed there was some problem.

I was on Windows at the time and opened up task manager as I do when I hear my computer is getting loud to see what was up and boy
was I in for a surprise, the CPU usage was crazy high! The map editor does have an inefficient loop but I am done with that because
my goal was just to get it working so we can start working on the map and so I can start working on the engine, but for the engine
I need to make this more efficient and better.

You could say we are coding from "scratch," but to really do something from scratch you need to recreate the universe. We are using
SDL2 to help with the audio, graphics, and other fun stuff. So I did a google search to try and figure out what I was doing. First
I stumbled upon this function called ```SDL_WaitEvent``` which helped some people. However, for a game this is not good because a
game is always going to be updating, even if there is no user input. I still thought ```SDL_PollEvent``` was the problem but there
is really nothing I can do about it, so I began to look at the game loop.

Our game loop looks like this:
```c++
#include "core.h"

int main(int argc, char* args[])
{
  const int FPS = 30;
  const int FRAME_DELAY = 1000 / FPS;

  Game::Core::init();

  while (Game::Core::is_running())
  {
    Uint32 frame_start = SDL_GetTicks();

    Game::Core::input();
    Game::Core::update();
    Game::Core::draw();

    int frame_time = SDL_GetTicks() - frame_start;

    while (FRAME_DELAY > frame_time)
    {
      Game::Core::input();
      frame_time = SDL_GetTicks() - frame_start;
    }
  }

  Game::Core::close();

  return 0;
}
```

```FRAME_DELAY``` is how many milliseconds there should be in between frames. and ```frame_time``` is how long it takes for the frame to finish. If the frame finishes early (less than ```FRAME_DELAY```), then we'll just handle inputs and update ```frame_time```.

I did some more reading and came upon ```SDL_Delay```, which will make a call to the OS's sleep function, this seems like
something which would work. My main worry is blocking the event polling, because in the past I tried something to handle framerate, but
there was delay between inputs (like the application would close slightly after pressing the X button).

I changed the while loop to become:
```c++
if (FRAME_DELAY > frame_time)
{
  SDL_Delay(FRAME_DELAY - frame_time);
}
```
This has reduced CPU usage to around the 20% range, which I can live with for now. I am hoping there is no lag within the game but I
can come back to this. If all else fails I can revert to this old loop which will work, even if the cpu gets hogged.
