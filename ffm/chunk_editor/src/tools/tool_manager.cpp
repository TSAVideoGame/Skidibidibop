#include "tool_manager.h"
#include "constants.h"
#include "window.h"

FFM::ChunkEditor::Tools::Manager::Manager(SDLW::Renderer* renderer)
{
  tabs.reserve(5);

  int width = 32;

  tabs.push_back(new Tabs::Main   (renderer, Constants::Window.TOOL_WIDTH - (width * 1), 0));
  tabs.push_back(new Tabs::Objects(renderer, Constants::Window.TOOL_WIDTH - (width * 2), 0));
  tabs.push_back(new Tab          (renderer, "Objs"  , Constants::Window.TOOL_WIDTH - (width * 3), 0, { 30, 140,  10}));
  tabs.push_back(new Tab          (renderer, "Monsts", Constants::Window.TOOL_WIDTH - (width * 4), 0, {160,  20,  10}));
  tabs.push_back(new Tab          (renderer, "NPCs"  , Constants::Window.TOOL_WIDTH - (width * 5), 0, { 10,  60,  160}));

  selected_tab = tabs[0];
  selected_tab->is_selected = true;
}

FFM::ChunkEditor::Tools::Manager::~Manager()
{
  for (Tab* t : tabs)
    delete t;
}

void FFM::ChunkEditor::Tools::Manager::update(MouseState ms)
{
  Inputs inputs = Window::get_inputs();

  switch (ms)
  {
    case MouseState::CLICK:
    {
      for (Tab* t : tabs)
      {
        if (t->is_hovered(inputs.mouse_x, inputs.mouse_y))
        {
          Window::selected_tool = nullptr;
          selected_tab->is_selected = false;
          selected_tab = t;
          selected_tab->is_selected = true;
          break;
        }
      }
    }
  }

  for (Tab* t : tabs)
    t->update(ms);
}

void FFM::ChunkEditor::Tools::Manager::draw()
{
  for (Tab* t : tabs)
    t->draw();
}
