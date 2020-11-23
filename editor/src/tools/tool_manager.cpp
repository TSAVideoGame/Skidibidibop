#include "tool_manager.h"
#include "window.h"

Editor::Tool::Manager::Manager(SDLW::Renderer* renderer)
{
  tabs.reserve(4);

  int y = Constants::Window.height - Constants::Window.toolBarHeight - Constants::Grid.size / 2;
  int width = Constants::Grid.size;

  tabs.push_back(new Tabs::Main(renderer, "Main",   0,                                     y, { 20,  20,  20}));
  tabs.push_back(new Tabs::Tile(renderer, "Tiles",  Constants::Window.width - (width * 1), y, { 30, 140,  10}));
  tabs.push_back(new Tab(renderer, "Player", Constants::Window.width - (width * 2), y, { 10,  60, 160}));
  tabs.push_back(new Tab(renderer, "Monst.", Constants::Window.width - (width * 3), y, {160,  20,  10}));

  selectedTab = tabs[0];
  selectedTab->isSelected = true;
}

Editor::Tool::Manager::~Manager()
{
  for (Tab* t : tabs)
    delete t;

  tabs.clear();
}

void Editor::Tool::Manager::update(MouseState ms)
{
  Inputs inputs = Window::get_inputs();
  // Update self
  switch (ms)
  {
    case MouseState::HOVER:
    {
      break;
    }
    case MouseState::CLICK:
    {
      // Select a new tab
      for (Tab* t : tabs)
      {
        if (t->isHovered(inputs.mouseX, inputs.mouseY))
        {
          Window::selected_tool = nullptr;
          selectedTab->isSelected = false;
          selectedTab = t;
          selectedTab->isSelected = true;
          break;
        }
      }
    }
  }

  // Update tabs
  for (Tab* t : tabs)
    t->update(ms);
}

void Editor::Tool::Manager::draw()
{
  for (Tab* t : tabs)
    t->draw();
}
