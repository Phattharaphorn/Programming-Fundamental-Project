#pragma once
#include "AllHeader.h"
#include "Score.h"
#define MAX_ITEMS 3 //play score exit

using namespace std;
using namespace sf;

class Menu
{
public:
	Menu(RenderWindow* window, Score* ss);
	~Menu();	

	void draw();
	void update();
	void MoveLeft();
	void MoveRight();
	inline int GetPressedItem() { return selectedItem; }

private:
	RenderWindow* window;
	Score* scoreScene; 
	sf::Texture backgroundTexture;
	Sprite background;
	int selectedItem;
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

};

