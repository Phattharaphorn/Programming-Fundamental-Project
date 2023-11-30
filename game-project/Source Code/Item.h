#pragma once
#include "AllHeader.h"

class Item
{
private:
	RectangleShape shape;

public:
	float lifeTime;

	Item(Texture* texture, Vector2f position, Vector2f size, float lt);
	void update(float deltaTime);
	void draw(RenderWindow& window);
	FloatRect getGlobalBounds();
};