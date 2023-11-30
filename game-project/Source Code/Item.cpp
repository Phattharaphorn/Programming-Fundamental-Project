#include "Item.h"

Item::Item(Texture* texture, Vector2f position, Vector2f size, float lt)
{
	shape.setTexture(texture);
	shape.setPosition(position);
	shape.setSize(size);
	lifeTime = lt;
}

void Item::update(float deltaTime)
{
	lifeTime -= deltaTime;
}

void Item::draw(RenderWindow& window)
{
	window.draw(shape);
}

FloatRect Item::getGlobalBounds()
{
	return shape.getGlobalBounds();
}
 