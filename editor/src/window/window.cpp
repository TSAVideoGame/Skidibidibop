#include "window.h"
#include "constants.h"
#include <ctime>
#include <SDL2/SDL_ttf.h>

bool Editor::Window::running;
SDLW::Window* Editor::Window::window;
SDLW::Renderer* Editor::Window::renderer;
Editor::Inputs Editor::Window::inputs;
Editor::Tool::Manager* Editor::Window::toolManager;
std::string Editor::Window::currentFile;
SDLW::Texture* Editor::Window::currentFileTex;
Data::Save::Data Editor::Window::data = Data::Save::load("res/default.sbbd");
SDLW::Texture* Editor::Window::spritesheet;
size_t Editor::Window::firstTile; // Top-left most tile
Editor::Tool::Base* Editor::Window::selectedTool = nullptr;

void Editor::Window::init()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

  window = new SDLW::Window("SBB Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants::Window.width, Constants::Window.height, 0);
  renderer = new SDLW::Renderer(window);
  inputs = {false, false, 0, 0, 0, 0, 0, 0, 0};
  running = true;
  toolManager = new Tool::Manager(renderer);
  spritesheet = new SDLW::Texture("res/spritesheet.png", renderer);

  // The default file name is SBBD_time.sbbd
  char timeNameBuffer[20];
  std::time_t rawtime;
  time(&rawtime);
  std::tm* timeinfo = localtime(&rawtime);
  strftime(timeNameBuffer, sizeof(timeNameBuffer), "%Y_%m_%d_%T", timeinfo);
  currentFile = "SBBD_";
  currentFile.append(timeNameBuffer);
  currentFile += ".sbbd";
  currentFileTex = nullptr;
  setCurrentFile(currentFile);

  firstTile = 0;
}

void Editor::Window::close()
{
  delete spritesheet;
  delete currentFileTex;
  delete toolManager;
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
    }
  }

  SDL_GetMouseState(&inputs.mouseX, &inputs.mouseY);
}

void Editor::Window::update()
{
  static unsigned int tempFirstTile = firstTile, tempViewX = firstTile % data.map.size.x, tempViewY = firstTile / data.map.size.y;
  if (inputs.mouseDown)
  {
    if (!inputs.oldMouseDown) // Click
    {
      toolManager->update(MouseState::CLICK);
    }
    // Drag
    if (selectedTool != nullptr)
    {
      toolManager->update(MouseState::DRAG);
    }
    // This camera movement is all broken
    else
    {
      int maxDrag = 29; // This will help in solving overflow messes

      int y = -((inputs.mouseY - inputs.clickMouseY) / Constants::Grid.size);
      int x = ((inputs.mouseX - inputs.clickMouseX) / Constants::Grid.size);

      // Make y within bounds
      if (tempFirstTile / data.map.size.x < maxDrag && static_cast<int>(tempFirstTile / data.map.size.x) + y < 0)
        y = -(tempFirstTile / data.map.size.x);
      else if (tempFirstTile / data.map.size.x + y >= data.map.size.y)
        y = (data.map.size.y - 1) - (tempFirstTile / data.map.size.x);

      // Make x within bounds
      if (tempFirstTile % data.map.size.x < maxDrag && static_cast<int>(tempFirstTile % data.map.size.x) + x < 0)
        x = -(tempFirstTile % data.map.size.x);
      else if (tempFirstTile % data.map.size.x + x >= data.map.size.x)
        x = (data.map.size.x - 1) - (tempFirstTile % data.map.size.x);

      // Change firstTile
      firstTile = tempFirstTile + data.map.size.x * y + x;
    }
  }

  if (!inputs.mouseDown && inputs.oldMouseDown)
  {
    if (selectedTool == nullptr)
    {
      tempFirstTile = firstTile;
      tempViewX = firstTile % data.map.size.x;
      tempViewY = firstTile / data.map.size.y;
    }
  }
}

static void drawGrid(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 36, 82, 94, 255);
  // Draw vertical lines
  for (int i = 1; i < Editor::Constants::Window.width / Editor::Constants::Grid.size; i++)
    SDL_RenderDrawLine(renderer, i * Editor::Constants::Grid.size, 0, i * Editor::Constants::Grid.size, Editor::Constants::Window.height);
  // Draw horizontal lines
  for (int i = 1; i < Editor::Constants::Window.height / Editor::Constants::Grid.size; i++)
    SDL_RenderDrawLine(renderer, 0, i * Editor::Constants::Grid.size, Editor::Constants::Window.width, i * Editor::Constants::Grid.size);
}

void Editor::Window::drawTiles()
{
  SDL_Rect dRect = {0, 0, Constants::Grid.size, Constants::Grid.size};
  SDL_Rect sRect = {0, 0, 32, 32};
  unsigned int windowXTiles = Constants::Window.width / Constants::Grid.size;
  unsigned int maxXTiles = data.map.size.x - (firstTile % data.map.size.x) < windowXTiles ? data.map.size.x - (firstTile % data.map.size.x) : windowXTiles;
  unsigned int windowYTiles = (Constants::Window.height - Constants::Window.toolBarHeight) / Constants::Grid.size;
  unsigned int maxYTiles = data.map.size.y - (firstTile / data.map.size.x) < windowYTiles ? data.map.size.y - (firstTile / data.map.size.x) : windowYTiles;

  for (unsigned int row = 0; row < maxYTiles; ++row)
  {
    for (unsigned int col = 0; col < maxXTiles; ++col)
    {
      sRect.x = data.map.tiles[firstTile + (row * data.map.size.x) + col].id * 32;
      renderer->copy(spritesheet, &sRect, &dRect);
      dRect.x += Constants::Grid.size;
    }

    dRect.x = 0;
    dRect.y += Constants::Grid.size;
  }
}

void Editor::Window::draw()
{
  renderer->setDrawColor(10, 56, 69, 255);
  renderer->clear();

  // Draw map stuff
  drawGrid(renderer->getSDL());
  drawTiles();

  // Draw tool stuff
  // Draw the toolbar
  SDL_Color c = toolManager->getColor();
  renderer->setDrawColor(c.r, c.g, c.b, 255);
  SDL_Rect toolbar = {0, Constants::Window.height - Constants::Window.toolBarHeight, Constants::Window.width, Constants::Window.toolBarHeight};
  SDL_RenderFillRect(renderer->getSDL(), &toolbar);
  toolManager->draw();

  // Draw the current file
  SDL_Rect dRect = {4, Constants::Window.height - 24, 0, 0};
  SDL_QueryTexture(currentFileTex->getSDL(), 0, 0, &dRect.w, &dRect.h);
  renderer->copy(currentFileTex, 0, &dRect);

  renderer->present();
}

void Editor::Window::setCurrentFile(const std::string& newFile)
{
  currentFile = newFile;
  std::string displayText = "File: " + newFile;
  
  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txtSurface = TTF_RenderText_Blended(font, displayText.c_str(), {255, 255, 255});
  if (currentFileTex != nullptr)
    delete currentFileTex;
  currentFileTex = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->getSDL(), txtSurface));
  SDL_FreeSurface(txtSurface);
  TTF_CloseFont(font);
}

bool Editor::Window::isRunning() { return running; }
Editor::Inputs Editor::Window::getInputs() { return inputs; }
std::string Editor::Window::getCurrentFile() { return currentFile; };
size_t Editor::Window::getFirstTile() { return firstTile; };
