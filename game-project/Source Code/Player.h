 #pragma once
#include "AllHeader.h"

class Player
{
public:
    Texture playerTexture;
	RectangleShape shape;
	Vector2f direction;
	float speed;
    CircleShape bullet;
    bool bulletStatus;
    float bulletSpeed;

    float invincibleTime;
    float currentInvincible;

	inline Player()
	{
        playerTexture.loadFromFile("Super.png");
		shape.setSize(Vector2f(120, 120));
		shape.setPosition(Vector2f(300, 400));
        shape.setTexture(&playerTexture);
		speed = 260;
        
        bullet.setRadius(10);
        bullet.setFillColor(Color::Red);
        bulletStatus = false;
        bulletSpeed = 600;

        invincibleTime = 5;
        currentInvincible = 0;
	}

    inline void reset()
    {
        shape.setPosition(Vector2f(300, 400));
        bulletStatus = false;
    }

	inline void update(float deltaTime)
	{
        direction = Vector2f(0, 0);
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            direction.y -= 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            direction.x -= 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            direction.y += 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            direction.x += 1;
        }
        shape.move(normalize(direction) * speed * deltaTime);

        Vector2f shapePos = shape.getPosition();
        Vector2f shapeSize = shape.getSize();
        if (shapePos.x < 0)
        {
            shapePos.x = 0;
        }
        if (shapePos.x > 800 - shapeSize.x)
        {
            shapePos.x = 800 - shapeSize.x;
        }
        if (shapePos.y < 0)
        {
            shapePos.y = 0;
        }
        if (shapePos.y > 600 - shapeSize.y)
        {
            shapePos.y = 600 - shapeSize.y;
        }
        shape.setPosition(shapePos);

        currentInvincible -= deltaTime;
        if (score % 1000 == 0 && score != 0)
        {
            currentInvincible = invincibleTime;
        }

        // Bullet
        if (Keyboard::isKeyPressed(Keyboard::Space) && !bulletStatus)
        {
            bulletStatus = true;
            Vector2f spawnPos = shapePos + (shapeSize / 2.f);
            spawnPos.x -= bullet.getRadius();
            bullet.setPosition(spawnPos);
        }
        if (bulletStatus)
        {
            bullet.move(Vector2f(0, -1) * bulletSpeed * deltaTime);
            if (bullet.getPosition().y < 0)
            {
                bulletStatus = false;
            }
        }
	}

    inline void checkHit(CircleShape enemyBullet, bool* enemyBulletStatus)
    {
        if (shape.getGlobalBounds().intersects(enemyBullet.getGlobalBounds()) && *enemyBulletStatus)
        {
            *enemyBulletStatus = false;
            if (currentInvincible < 0)
                heart--;
        }
    }

    inline FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }

    inline void render(RenderWindow *window)
    {
        if (bulletStatus)
        {
            window->draw(bullet);
        }
        window->draw(shape);
    }
};