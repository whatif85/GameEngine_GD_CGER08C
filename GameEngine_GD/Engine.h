#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "ECS.h"
#include "Components.h"
#include "RenderingSystem.h"


class Engine
{
private:
	Engine();
	
	// Singleton: required to prevent the reference from being copied, moved, or assigned
	Engine(Engine& copy);				// hide copy constructor
	Engine(Engine&& other);				// hide move constructor (&& reference of value)
	Engine& operator= (Engine& copy);	// hide assignment operator

	~Engine();

	void Update();

public:
	bool bIsQuit;
	sf::RenderWindow* window;
	ECS::World* world;

	static Engine& GetInstance();
	void Start(sf::RenderWindow* win);
	void AddSystem(ECS::EntitySystem* newSys);
};

