#pragma once
#include "AllHeader.h"
#define SCORE_ITEMS 2 //back exit 
class Score
{
public:
	 Score(float width, float height);
	~Score();

	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void MoveLeft();
	void MoveRight();
	void loadScore();

private:
	int selectedItem;
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Font font;
	sf::Text score[SCORE_ITEMS]; //back exit 
	sf::Texture scoreTexture;
	sf::Sprite scoreSprite;

	Text nameTexts[5];
	Text scoreTexts[5];
};

