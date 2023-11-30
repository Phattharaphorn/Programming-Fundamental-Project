#pragma once
#include "AllHeader.h"

class Space
{
public:
	RectangleShape space;
	Vector2f start;
	Vector2f end;
	float spaceSpeed;
	float spaceRatio;

	CircleShape bullet;
	bool bulletStatus;
	float bulletSpeed;

	float currentSpawn;
	float respawnTime;
	bool died;

	inline Space(Texture *spaceTexture, Vector2f startPos, Vector2f endPos)
	{
		space.setSize(Vector2f(100, 100));
		// space.setPosition(Vector2f(100, 100));
		space.setTexture(spaceTexture);
		start = startPos;
		end = endPos;
		spaceSpeed = (rand() % 50 + 50) / 100.f;
		spaceRatio = rand();

		currentSpawn = 0;
		respawnTime = 2;
		died = false;

		bullet.setRadius(10);
		bullet.setFillColor(Color::Green);
		bulletStatus = false;
		bulletSpeed = 400;
	}

	inline void reset()
	{
		died = false;
		currentSpawn = 0;
		bulletStatus = false;
		spaceSpeed = (rand() % 50 + 50) / 100.f;
		spaceRatio = rand();
	}

	inline void update(float deltaTime, CircleShape playerBullet, bool *playerBulletStatus)
	{
		if (died)
		{
			currentSpawn += deltaTime;
			if (currentSpawn >= respawnTime)
			{
				currentSpawn = 0;
				died = false;
			}
			return;
		}

		// update Space
		spaceRatio += spaceSpeed * deltaTime;
		Vector2f spacePos = start + ((end - start) * sin(spaceRatio)); 
		space.setPosition(spacePos);

		// get Hit
		if (space.getGlobalBounds().intersects(playerBullet.getGlobalBounds()) && *playerBulletStatus)
		{
			died = true;
			bulletStatus = false;
			*playerBulletStatus = false;
			score += 100;
		}

		// update Bullet
		if (!bulletStatus)
		{
			bulletStatus = true;
			Vector2f spawnPos = space.getPosition() + (space.getSize() / 2.f);
			spawnPos.x -= bullet.getRadius();
			bullet.setPosition(spawnPos);
		}
		if (bulletStatus)
		{
			bullet.move(Vector2f(0, 1) * bulletSpeed * deltaTime);
			if (bullet.getPosition().y > 600)
			{
				bulletStatus = false;
			}
		}
	}

	inline void render(RenderWindow* window)
	{
		if (died)
			return;
		if (bulletStatus)
		{
			window->draw(bullet);
		}
		window->draw(space);
	}

	inline void setTexture(Texture* spaceTexture)
	{
		space.setTexture(spaceTexture);
	}
};