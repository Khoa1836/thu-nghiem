// Scene.cpp
#include "Scene.h"
#include "GameManager.h"

void Scene::update(float deltaTime) {
	for (auto& obj : gameObjects)
	{
		if (obj->needDeleted) 
		{
			obj = nullptr; // Mark for deletion
			continue;
		}
		obj->update(deltaTime);
	}

	// Remove null pointers from the gameObjects vector
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), nullptr), gameObjects.end());

	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			if (gameObjects[i]->getHitbox().getGlobalBounds().intersects(gameObjects[j]->getHitbox().getGlobalBounds()))
			{
				gameObjects[i]->onCollisionEnter(gameObjects[j]);
				gameObjects[j]->onCollisionEnter(gameObjects[i]);
			}
		}
	}
}

void Scene::render(sf::RenderWindow& window) {
	window.setView(this->camera.getView(window.getSize()));
	for (auto& obj : gameObjects) obj->render(window);
}