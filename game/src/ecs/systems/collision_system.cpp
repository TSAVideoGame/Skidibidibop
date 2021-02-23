#include "collision_system.h"
#include "collision_component.h"
#include "transform_component.h"
#include "line_component.h"
#include "physics_component.h"
#include "core.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Collision> Game::ECS::Systems::collision_system;

void Game::ECS::Systems::Collision::update()
{
	Components::CollisionManager* cm = Components::Manager::get_instance().get_component<Components::CollisionManager>();
	Components::LineManager* lm = Components::Manager::get_instance().get_component<Components::LineManager>();
	Components::PhysicsManager* pm = Components::Manager::get_instance().get_component<Components::PhysicsManager>();

	for (std::size_t i = 1; i < cm->data.instances; ++i) 
	{

		AABB hitBox = get_AABB(cm->data.entity[i]);
		std::uint32_t rectMinX = hitBox.x;
		std::uint32_t rectMaxX = hitBox.x + hitBox.w;
		std::uint32_t rectMinY = hitBox.y;
		std::uint32_t rectMaxY = hitBox.y + hitBox.h;
		//Core::logger.log(Logger::LOG, "\nRectMinX: " + std::to_string(rectMinX) + "\nRectMaxX: " + std::to_string(rectMaxX));
		for (std::size_t j = 1; j < lm->data.instances; ++j) 
		{

			//X PORTION

			std::uint32_t minX = lm->data.v1_x[j];
			std::uint32_t maxX = lm->data.v2_x[j];
			//checks and fixes Min/Max
			if (minX > maxX) 
			{
				minX = lm->data.v2_x[j];
				maxX = lm->data.v1_x[j];
			}
			//Core::logger.log(Logger::LOG, "MinX: " + std::to_string(minX) + "\nMaxX: " + std::to_string(maxX));

			//compare x projections
			if (maxX > rectMaxX) 
			{
				maxX = rectMaxX;
			}

			if (minX < rectMinX) 
			{
				minX = rectMinX;
			}

			if (minX > maxX) 
			{
				Core::logger.log(Logger::LOG, "Failed X axis");
				continue;
			}
			Core::logger.log(Logger::LOG, "Succeeded X axis");

			//Y PORTION
			std::uint32_t minY = lm->data.v1_y[j];
			std::uint32_t maxY = lm->data.v2_y[j];

			int dxTemp = lm->data.v2_x[j] - lm->data.v1_x[j];
			double dx = dxTemp;
			//checks and fixes min/max for y
			if (dx != 0) 
			{
				double m = (lm->data.v2_y[j] - lm->data.v1_y[j]) / dx;
				int b = lm->data.v1_y[j] - m * lm->data.v1_x[j];
				minY = m * minX + b;
				maxY = m * maxX + b;
			}

			if (minY > maxY)
			{
				std::uint32_t temp = maxY;
				maxY = minY;
				minY = temp;
			}
			
			//compare Y projections
			if (maxY > rectMaxY)
			{
				maxY = rectMaxY;
			}

			if (minY < rectMinY)
			{
				minY = rectMinY;
			}

			if (minY > maxY)
			{
				Core::logger.log(Logger::LOG, "Failed Y axis");
				continue;
			}

			Core::logger.log(Logger::LOG, "Collided");
			Components::PhysicsManager::Instance pi = pm->get_instance(cm->data.entity[i]);
			if (pi.index != 0)
			{
				pm->set_x_vel(pi, -10 * pm->get_x_vel(pi));
				pm->set_y_vel(pi, -10 * pm->get_y_vel(pi));
			}
		}
	}
}

Game::ECS::Systems::Collision::AABB Game::ECS::Systems::Collision::get_AABB(Entity entity)
{
  AABB hitbox;

  Components::CollisionManager* cm = Components::Manager::get_instance().get_component<Components::CollisionManager>(); 
  Components::CollisionManager::Instance cmi = cm->get_instance(entity);
  Components::TransformManager* tm = Components::Manager::get_instance().get_component<Components::TransformManager>(); 
  Components::TransformManager::Instance tmi = tm->get_instance(entity);

  hitbox.x = tm->get_x(tmi) + cm->get_offset_x(cmi);
  hitbox.y = tm->get_y(tmi) + cm->get_offset_y(cmi);
  hitbox.w = cm->get_width(cmi);
  hitbox.h = cm->get_height(cmi);
  
  return hitbox;
}
