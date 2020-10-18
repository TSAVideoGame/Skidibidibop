#include "tool_manager.h"

Editor::Tool::Manager::Manager(SDLW::Renderer* renderer)
{
  tabs.reserve(4);

  int y = Constants::Window.height - Constants::Window.toolBarHeight - Constants::Grid.size;
  int width = Constants::Grid.size * 2;

  tabs.push_back(new Tab(renderer, "Main",   0,                                     y, { 20,  20,  20}));
  tabs.push_back(new Tab(renderer, "Tiles",  Constants::Window.width - (width * 1), y, { 20, 160,  20}));
  tabs.push_back(new Tab(renderer, "Player", Constants::Window.width - (width * 2), y, { 10,  60, 160}));
  tabs.push_back(new Tab(renderer, "Monst.", Constants::Window.width - (width * 3), y, {160,  20,  10}));

  selectedTab = tabs[0];
}

Editor::Tool::Manager::~Manager()
{
  for (Tab* t : tabs)
    delete t;

  tabs.clear();
}

void Editor::Tool::Manager::update(MouseState ms, Inputs inputs)
{
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
          selectedTab = t;
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
