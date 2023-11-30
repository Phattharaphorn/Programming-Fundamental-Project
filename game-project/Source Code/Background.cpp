#include "Background.h"
Background::Background(sf::Texture* texture, float speed)
{
	this->speed = speed;
	this->size = sf::Vector2f(800.0f, 600.0f);
	body[0].setSize(size);
	body[1].setSize(size);
	body[0].setTexture(texture);
	body[1].setTexture(texture);  

	if (speed < 0) //left
		body[1].setPosition(size.x - 2.0f, 0.0f);
	else body[1].setPosition(-size.x + 2.0f, 0.0f);
}

void Background::Update(float deltatime)
{
	for (int i = 0; i < 2; i++)
	{
		position = body[i].getPosition();

		body[i].move(speed * deltatime, 0);
		
		if (position.x <= -size.x && speed < 0)
			body[i].setPosition(size.x - 4.0f, position.y);
		else if (position.x >= size.x && speed > 0)
			body[i].setPosition(-size.x + 4.0f, position.y);
   }
}
void Background::Draw(sf::RenderWindow& window)
{
	window.draw(body[0]);
	window.draw(body[1]);
}

