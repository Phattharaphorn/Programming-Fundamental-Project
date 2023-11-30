#pragma once
#include "Player.h"
#include "Space.h"
#include "Background.h"
#include "Item.h"
#define maxHeart 10

class Game
{
private:
	RenderWindow* window;
	Texture spaceTexture;
	Player player;
	Space space;
	Space space2;
	Space space3;
	Font font;
	Text scoreText;
	Texture heartTexture;
	Sprite hearts[maxHeart];
	Vector2f heartStartPos;
	Texture backgroundTexture[3];
	vector<Background> backgrounds;
	vector<Item> items;
	Texture itemTexture;
	bool isItemSpawning;
	float itemSpawnRate;
	float currentItemSpawn;

public:
	Game(RenderWindow* window);
	void update(float deltaTime);
	void render(); 
	void reset(); 
	void spawnItem(float deltaTime);
};

