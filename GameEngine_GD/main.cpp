#include <SFML\Graphics.hpp>
#include "Engine.h"


int main(int argc, char* args[])
{
	// Declare and get instance of singleton
	Engine& gameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");

	// Create world for attaching entities and systems to
	gameEngine.world = ECS::World::createWorld();
	ECS::Entity* ent;

	// Add systems to engine
	gameEngine.AddSystem(new RenderingSystem());

	// Create and assign 250 entities to the world
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			ent = gameEngine.world->create();

			// Assign components to entities after creation
			ent->assign<Transform>(i * 25, j * 32);
			ent->assign<Sprite>("../Debug/Images/herosheet.png");

			std::cout << ent->getEntityId() << " is the entity ID." << std::endl;
		}
	}

	// Pass window reference to engine and start
	gameEngine.Start(&window);

	return 0;
}