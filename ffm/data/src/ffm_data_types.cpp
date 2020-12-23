#include "ffm_data_types.h"

/*
 * ========================================
 * Chunk
 *
 * A Chunk of the map
 * ========================================
 */
FFM::Data::Types::Chunk::Chunk()
{
  x = 0;
  y = 0;
  background_id = 0;
  num_vertices = 0;
  num_lines = 0;
  num_objects = 0;
  num_enemies = 0;
}

FFM::Data::Types::Chunk::Chunk(std::ifstream& file)
{
  load(file);
}

void FFM::Data::Types::Chunk::save(std::ofstream& file)
{
  // Save the chunk position
  file.write(reinterpret_cast<char*>(&x), sizeof(x));
  file.write(reinterpret_cast<char*>(&y), sizeof(y));

  file.write(reinterpret_cast<char*>(&background_id), sizeof(background_id));

  // Save Vertices
  num_vertices = vertices.size();
  file.write(reinterpret_cast<char*>(&num_vertices), sizeof(num_vertices));
  for (std::vector<Vertex>::iterator i = vertices.begin(); i < vertices.end(); ++i)
  {
    file.write(reinterpret_cast<char*>(&(*i).x), sizeof((*i).x));
    file.write(reinterpret_cast<char*>(&(*i).y), sizeof((*i).y));
  }

  // Save Lines
  num_lines = lines.size();
  file.write(reinterpret_cast<char*>(&num_lines), sizeof(num_lines));
  for (std::vector<Line>::iterator i = lines.begin(); i < lines.end(); ++i)
  {
    file.write(reinterpret_cast<char*>(&(*i).vertex_1), sizeof((*i).vertex_1));
    file.write(reinterpret_cast<char*>(&(*i).vertex_2), sizeof((*i).vertex_2));
    file.write(reinterpret_cast<char*>(&(*i).flag), sizeof((*i).flag));
  }

  // Save Objectss
  num_objects = objects.size();
  file.write(reinterpret_cast<char*>(&num_objects), sizeof(num_objects));
  for (std::vector<Object>::iterator i = objects.begin(); i < objects.end(); ++i)
  {
    file.write(reinterpret_cast<char*>(&(*i).vertex), sizeof((*i).vertex));
    file.write(reinterpret_cast<char*>(&(*i).id), sizeof((*i).id));
  }

  // Save Enemies
  num_enemies = enemies.size();
  file.write(reinterpret_cast<char*>(&num_enemies), sizeof(num_enemies));
  for (std::vector<Enemy>::iterator i = enemies.begin(); i < enemies.end(); ++i)
  {
    file.write(reinterpret_cast<char*>(&(*i).vertex), sizeof((*i).vertex));
    file.write(reinterpret_cast<char*>(&(*i).id), sizeof((*i).id));
  }

  // Save NPCs
  num_npcs = npcs.size();
  file.write(reinterpret_cast<char*>(&num_npcs), sizeof(num_npcs));
  for (std::vector<NPC>::iterator i = npcs.begin(); i < npcs.end(); ++i)
  {
    file.write(reinterpret_cast<char*>(&(*i).vertex), sizeof((*i).vertex));
    file.write(reinterpret_cast<char*>(&(*i).id), sizeof((*i).id));
  }
}

void FFM::Data::Types::Chunk::load(std::ifstream& file)
{
  // Load the chunk position
  file.read(reinterpret_cast<char*>(&x), sizeof(x));
  file.read(reinterpret_cast<char*>(&y), sizeof(y));

  file.read(reinterpret_cast<char*>(&background_id), sizeof(background_id));
  // Load the vertices
  file.read(reinterpret_cast<char*>(&num_vertices), sizeof(num_vertices));
  vertices.reserve(num_vertices);
  for (std::size_t i = 0; i < num_vertices; ++i)
  {
    Vertex v;
    file.read(reinterpret_cast<char*>(&v.x), sizeof(v.x));
    file.read(reinterpret_cast<char*>(&v.y), sizeof(v.y));
    vertices.push_back(v);
  }

  // Load the lines
  file.read(reinterpret_cast<char*>(&num_lines), sizeof(num_lines));
  lines.reserve(num_lines);
  for (std::size_t i = 0; i < num_lines; ++i)
  {
    Line l;
    file.read(reinterpret_cast<char*>(&l.vertex_1), sizeof(l.vertex_1));
    file.read(reinterpret_cast<char*>(&l.vertex_2), sizeof(l.vertex_2));
    file.read(reinterpret_cast<char*>(&l.flag), sizeof(l.flag));
    lines.push_back(l);
  }

  // Load the objects
  file.read(reinterpret_cast<char*>(&num_objects), sizeof(num_objects));
  objects.reserve(num_objects);
  for (std::size_t i = 0; i < num_objects; ++i)
  {
    Object o;
    file.read(reinterpret_cast<char*>(&o.vertex), sizeof(o.vertex));
    file.read(reinterpret_cast<char*>(&o.id), sizeof(o.id));
    objects.push_back(o);
  }

  // Load the enemies
  file.read(reinterpret_cast<char*>(&num_enemies), sizeof(num_enemies));
  enemies.reserve(num_enemies);
  for (std::size_t i = 0; i < num_enemies; ++i)
  {
    Enemy e;
    file.read(reinterpret_cast<char*>(&e.vertex), sizeof(e.vertex));
    file.read(reinterpret_cast<char*>(&e.id), sizeof(e.id));
    enemies.push_back(e);
  }

  // Load the npcs
  file.read(reinterpret_cast<char*>(&num_npcs), sizeof(num_npcs));
  npcs.reserve(num_npcs);
  for (std::size_t i = 0; i < num_npcs; ++i)
  {
    NPC n;
    file.read(reinterpret_cast<char*>(&n.vertex), sizeof(n.vertex));
    file.read(reinterpret_cast<char*>(&n.id), sizeof(n.id));
    npcs.push_back(n);
  }
}

void FFM::Data::Types::Chunk::clean()
{
  // TODO
}
