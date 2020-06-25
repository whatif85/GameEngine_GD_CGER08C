#include "RenderingSystem.h"


RenderingSystem::RenderingSystem()
{
}

RenderingSystem::~RenderingSystem()
{
}

void RenderingSystem::tick(ECS::World* world, float deltaTime)
{
	// Clear before drawing textures
	Engine::GetInstance().window->clear();
	
	// Call "each" function to be passed to a one-time lambda function.
	// Pass entity, transform, and sprite by reference
	// We want to pass in our entity (pointer), and a component handle for each component
	world->each<Transform, Sprite>(
		[&](ECS::Entity* ent,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Sprite> sprite) -> void
	{
		// Add texture to map
		if (textureMap.count(sprite->texture) < 1)
		{
			textureMap[sprite->texture] = LoadTexture(sprite->texture);
		}

		// If no texture is found, add it
		if (sprite->sprite.getTexture() == NULL)
		{
			sprite->sprite.setTexture(*textureMap[sprite->texture]);
			sprite->width  = sprite->sprite.getGlobalBounds().width;
			sprite->height = sprite->sprite.getGlobalBounds().height;
		}

		// Update and draw to screen
		sprite->sprite.setPosition(transform->X, transform->Y);
		Engine::GetInstance().window->draw(sprite->sprite);
	});

	// Display updates
	Engine::GetInstance().window->display();
}

sf::Texture* RenderingSystem::LoadTexture(std::string Texture)
{
	sf::Texture* _tex = new sf::Texture();

	// if the loaded texture from file is not found
	if (_tex->loadFromFile(Texture) == NULL)
	{
		std::cerr << "Unable to load image " << Texture << "./nIs this image the correct directory?" << std::endl;
		std::cerr << "Error: " << std::endl;

		exit(EXIT_FAILURE);
	}

	return _tex;
}
