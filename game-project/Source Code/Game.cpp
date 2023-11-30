#include "Game.h"

int heart = maxHeart;
int score = 0;

Game::Game(RenderWindow* window) :
	space(nullptr, Vector2f(100, 100), Vector2f(200, 100)),
	space2(nullptr, Vector2f(320, 0), Vector2f(420, 0)),
	space3(nullptr, Vector2f(550, 100), Vector2f(650, 100))
{
	this->window = window;
	spaceTexture.loadFromFile("space.png");
	space.setTexture(&spaceTexture);
	space2.setTexture(&spaceTexture);
	space3.setTexture(&spaceTexture);
	font.loadFromFile("CourierPrime.ttf");
	scoreText.setFont(font);
	scoreText.setString("Score: " + to_string(score));
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(Color::White);
	heartTexture.loadFromFile("heart.png");
	heartStartPos = Vector2f(0, 560);
	for (int i = 0; i < maxHeart; i++)
	{
		hearts[i].setTexture(heartTexture);
		hearts[i].setScale(Vector2f(0.1, 0.1));
		hearts[i].setPosition(heartStartPos + Vector2f(50 * i, 0));
	}
	backgroundTexture[0].loadFromFile("./backgrounds/background8.jpg");
	backgroundTexture[1].loadFromFile("./backgrounds/background8.jpg");
	backgroundTexture[2].loadFromFile("./backgrounds/background8.jpg");
	backgrounds.push_back(Background(&backgroundTexture[0], -60.f));
	backgrounds.push_back(Background(&backgroundTexture[1], -80.f));
	backgrounds.push_back(Background(&backgroundTexture[2], -60.f));

	itemTexture.loadFromFile("item.png");
	isItemSpawning = false;
	itemSpawnRate = 5;
	currentItemSpawn = 0;
}

void Game::update(float deltaTime)
{
	Event ev;
	while (window->pollEvent(ev))
	{
		if (ev.type == Event::Closed)
			window->close();
	}
	player.update(deltaTime);
	space.update(deltaTime, player.bullet, &player.bulletStatus);
	space2.update(deltaTime, player.bullet, &player.bulletStatus);
	space3.update(deltaTime, player.bullet, &player.bulletStatus);
	player.checkHit(space.bullet, &space.bulletStatus);
	player.checkHit(space2.bullet, &space2.bulletStatus);
	player.checkHit(space3.bullet, &space3.bulletStatus);

	scoreText.setString("Score: " + to_string(score));

	if (heart == 0)
	{
		state = OverState;
		reset();
	}

	for (Background& background : backgrounds)
		background.Update(deltaTime);

	spawnItem(deltaTime);

	for (int i = 0; i < items.size(); i++)
	{
		items[i].update(deltaTime);
		if (player.getGlobalBounds().intersects(items[i].getGlobalBounds()))
		{
			heart++;
			items.erase(items.begin() + i);
			continue;
		}
		if (items[i].lifeTime < 0)
		{
			items.erase(items.begin() + i);
			continue;
		}
	}
}

void Game::render()
{
	for (Background& background : backgrounds)
		background.Draw(*window);
	space.render(window);
	space2.render(window);
	space3.render(window);
	player.render(window);
	window->draw(scoreText);
	for (int i = 0; i < items.size(); i++)
	{
		items[i].draw(*window);
	}
	for (int i = 0; i < heart; i++)
	{
		window->draw(hearts[i]);
	}
}

void Game::reset()
{
	isItemSpawning = false;
	itemSpawnRate = 5;
	currentItemSpawn = 0;
	heart = maxHeart;
	player.reset();
	space.reset();
	space2.reset();
	space3.reset();
	items.clear();
}

void Game::spawnItem(float deltaTime)
{
	if (heart <= 5)
	{
		isItemSpawning = true;
	}
	else if (heart == maxHeart)
	{
		isItemSpawning = false;
	}

	if (isItemSpawning)
	{
		currentItemSpawn += deltaTime;
		if (currentItemSpawn >= itemSpawnRate)
		{
			currentItemSpawn = 0;
			int randomX = randint(0, 799 - 50);
			int randomY = randint(200, 500);
			items.push_back(Item(&itemTexture, Vector2f(randomX, randomY), Vector2f(50, 50), 5));
		}
	}
}
