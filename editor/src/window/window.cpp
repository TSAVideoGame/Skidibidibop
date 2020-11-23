#include "window.h"
#include "constants.h"
#include <ctime>
#include <SDL2/SDL_ttf.h>

bool Editor::Window::running = true;
SDLW::Window* Editor::Window::window;
SDLW::Renderer* Editor::Window::renderer;
Editor::Inputs Editor::Window::inputs;
Editor::Tool::Manager* Editor::Window::tool_manager;
std::string Editor::Window::current_file;
SDLW::Texture* Editor::Window::current_file_tex;
unsigned int Editor::Window::current_section = 0;
unsigned int Editor::Window::current_zoom = 1;
Data::Save::Data Editor::Window::data = Data::Save::load("res/default.sbbd");
SDLW::Texture* Editor::Window::spritesheet;
size_t Editor::Window::firstTile; // Top-left most tile
Editor::Tool::Base* Editor::Window::selected_tool = nullptr;

void Editor::Window::init()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

  window = new SDLW::Window("SBB Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants::Window.width, Constants::Window.height, 0);
  renderer = new SDLW::Renderer(window);
  inputs = {false, false, 0, 0, 0, 0, 0, 0, 0};
  tool_manager = new Tool::Manager(renderer);
  spritesheet = new SDLW::Texture("res/spritesheet.png", renderer);

  // The default file name is SBBD_time.sbbd
  char timeNameBuffer[20];
  std::time_t rawtime;
  time(&rawtime);
  std::tm* timeinfo = localtime(&rawtime);
  strftime(timeNameBuffer, sizeof(timeNameBuffer), "%Y_%m_%d_%T", timeinfo);
  current_file = "SBBD_";
  current_file.append(timeNameBuffer);
  current_file += ".sbbd";
  current_file_tex = nullptr;
  set_current_file(current_file);

  firstTile = 0;
}

void Editor::Window::close()
{
  delete spritesheet;
  delete current_file_tex;
  delete tool_manager;
  delete renderer;
  delete window;

  TTF_Quit();
  SDL_Quit();
}

void Editor::Window::input()
{
  inputs.oldMouseDown = inputs.mouseDown;
  inputs.oldMouseX = inputs.mouseX;
  inputs.oldMouseY = inputs.mouseY;
  inputs.mouseWheelY = 0;

  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
      {
        running = false;
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            inputs.mouseDown = true;
            if (!inputs.oldMouseDown)
              SDL_GetMouseState(&inputs.clickMouseX, &inputs.clickMouseY);
            break;
          }
        }
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            inputs.mouseDown = false;
            break;
          }
        }
        break;
      }
      case SDL_MOUSEWHEEL:
      {
        inputs.mouseWheelY = e.wheel.y;
        break;
      }
      case SDL_WINDOWEVENT:
      {
        if (SDL_GetWindowID(window->get_SDL()) != e.window.windowID)
        {
          inputs.mouseDown = false;
        }
        break;
      }
    }
  }

  SDL_GetMouseState(&inputs.mouseX, &inputs.mouseY);
}

void Editor::Window::update()
{
  static unsigned int tempFirstTile = firstTile, tempViewX = firstTile % data.map.sections[current_section].size.x, tempViewY = firstTile / data.map.sections[current_section].size.y;
  if (inputs.mouseDown)
  {
    if (!inputs.oldMouseDown) // Click
    {
      tool_manager->update(MouseState::CLICK);
    }
    // Drag
    if (selected_tool != nullptr)
    {
      tool_manager->update(MouseState::DRAG);
    }
    // This camera movement is all broken
    else
    {
      int maxDrag = 29; // This will help in solving overflow messes

      int y = -((inputs.mouseY - inputs.clickMouseY) / Constants::Grid.size);
      int x = ((inputs.mouseX - inputs.clickMouseX) / Constants::Grid.size);

      // Make y within bounds
      if (tempFirstTile / data.map.sections[current_section].size.x < maxDrag && static_cast<int>(tempFirstTile / data.map.sections[current_section].size.x) + y < 0)
        y = -(tempFirstTile / data.map.sections[current_section].size.x);
      else if (tempFirstTile / data.map.sections[current_section].size.x + y >= data.map.sections[current_section].size.y)
        y = (data.map.sections[current_section].size.y - 1) - (tempFirstTile / data.map.sections[current_section].size.x);

      // Make x within bounds
      if (tempFirstTile % data.map.sections[current_section].size.x < maxDrag && static_cast<int>(tempFirstTile % data.map.sections[current_section].size.x) + x < 0)
        x = -(tempFirstTile % data.map.sections[current_section].size.x);
      else if (tempFirstTile % data.map.sections[current_section].size.x + x >= data.map.sections[current_section].size.x)
        x = (data.map.sections[current_section].size.x - 1) - (tempFirstTile % data.map.sections[current_section].size.x);

      // Change firstTile
      firstTile = tempFirstTile + data.map.sections[current_section].size.x * y + x;
    }
  }

  // Release
  if (!inputs.mouseDown && inputs.oldMouseDown)
  {
    if (selected_tool == nullptr)
    {
      tempFirstTile = firstTile;
      tempViewX = firstTile % data.map.sections[current_section].size.x;
      tempViewY = firstTile / data.map.sections[current_section].size.y;
    }
  }

  // Scroll
  if (std::abs(inputs.mouseWheelY) > 0)
  {
    if (inputs.mouseWheelY > 0) // Decrease zoom
    {
      if (current_zoom > 0)
        --current_zoom;
    }
    else // Increase zoom
    {
      if (current_zoom < 4)
        ++current_zoom;
    }
  }
}

static void drawGrid(SDL_Renderer* renderer)
{
  int size = 32;
  SDL_SetRenderDrawColor(renderer, 36, 82, 94, 255);
  // Draw vertical lines
  for (int i = 1; i < Editor::Constants::Window.width / size; i++)
    SDL_RenderDrawLine(renderer, i * size, 0, i * size, Editor::Constants::Window.height);
  // Draw horizontal lines
  for (int i = 1; i < Editor::Constants::Window.height / size; i++)
    SDL_RenderDrawLine(renderer, 0, i * size, Editor::Constants::Window.width, i * size);
}

void Editor::Window::draw_tiles()
{
  int size = Constants::Grid.size / std::pow(2, current_zoom);
  SDL_Rect dRect = {0, 0, size, size};
  SDL_Rect sRect = {0, 0, 32, 32};
  unsigned int windowXTiles = Constants::Window.width / size;
  unsigned int maxXTiles = data.map.sections[current_section].size.x - (firstTile % data.map.sections[current_section].size.x) < windowXTiles ? data.map.sections[current_section].size.x - (firstTile % data.map.sections[current_section].size.x) : windowXTiles;
  unsigned int windowYTiles = (Constants::Window.height - Constants::Window.toolBarHeight) / size;
  unsigned int maxYTiles = data.map.sections[current_section].size.y - (firstTile / data.map.sections[current_section].size.x) < windowYTiles ? data.map.sections[current_section].size.y - (firstTile / data.map.sections[current_section].size.x) : windowYTiles;

  for (unsigned int row = 0; row < maxYTiles; ++row)
  {
    for (unsigned int col = 0; col < maxXTiles; ++col)
    {
      sRect.x = data.map.sections[current_section].tiles[firstTile + (row * data.map.sections[current_section].size.x) + col].id * 32;
      renderer->copy(spritesheet, &sRect, &dRect);
      dRect.x += size;
    }

    dRect.x = 0;
    dRect.y += size;
  }
}

void Editor::Window::draw()
{
  renderer->set_draw_color(10, 56, 69, 255);
  renderer->clear();

  // Draw map stuff
  drawGrid(renderer->get_SDL());
  draw_tiles();

  // Draw tool stuff
  // Draw the toolbar
  SDL_Color c = tool_manager->getColor();
  renderer->set_draw_color(c.r, c.g, c.b, 255);
  SDL_Rect toolbar = {0, Constants::Window.height - Constants::Window.toolBarHeight, Constants::Window.width, Constants::Window.toolBarHeight};
  SDL_RenderFillRect(renderer->get_SDL(), &toolbar);
  tool_manager->draw();

  // Draw the current file
  SDL_Rect dRect = {4, Constants::Window.height - 24, 0, 0};
  SDL_QueryTexture(current_file_tex->get_SDL(), 0, 0, &dRect.w, &dRect.h);
  renderer->copy(current_file_tex, 0, &dRect);

  renderer->present();
}

void Editor::Window::set_current_file(const std::string& newFile)
{
  current_file = newFile;
  std::string displayText = "File: " + newFile;
  
  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txtSurface = TTF_RenderText_Blended(font, displayText.c_str(), {255, 255, 255});
  if (current_file_tex != nullptr)
    delete current_file_tex;
  current_file_tex = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txtSurface));
  SDL_FreeSurface(txtSurface);
  TTF_CloseFont(font);
}

bool Editor::Window::is_running() { return running; }
Editor::Inputs Editor::Window::get_inputs() { return inputs; }
std::string Editor::Window::get_current_file() { return current_file; };
size_t Editor::Window::getFirstTile() { return firstTile; };
