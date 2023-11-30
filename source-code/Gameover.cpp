#include "Gameover.h"

Gameover::Gameover(float width, float height)
{
	this->size = sf::Vector2f(800.0f, 600.0f);
	selectedItem = 0;

	gameoverTexture.loadFromFile("backgroundover1.jpg");
	gameoverSprite.setTexture(gameoverTexture);

	if(!font.loadFromFile("SDfont.ttf"))
	{
		//handle error
	}
	gameover[0].setFont(font);
	gameover[0].setCharacterSize(60);
	gameover[0].setFillColor(sf::Color::Yellow);
	gameover[0].setString("Back");
	gameover[0].setOrigin(gameover[0].getGlobalBounds().width / 2, gameover[0].getGlobalBounds().height / 1);
	gameover[0].setPosition(sf::Vector2f(width * 0.5, height * 0.75));

	gameover[1].setFont(font);
	gameover[1].setCharacterSize(60);
	gameover[1].setFillColor(sf::Color(224, 250, 132));
	gameover[1].setString("Exit");
	gameover[1].setOrigin(gameover[1].getGlobalBounds().width / 2, gameover[1].getGlobalBounds().height / 2);
	gameover[1].setPosition(sf::Vector2f(width * 0.5, height * 0.83));

	scoreText.setFont(font);
	scoreText.setCharacterSize(60);
	scoreText.setFillColor(sf::Color(252, 157, 61));
	scoreText.setString("Score : ");
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
	scoreText.setPosition(sf::Vector2f(width * 0.5, height * 0.45));

	nameText.setFont(font);
	nameText.setCharacterSize(60);
	nameText.setFillColor(sf::Color(252, 157, 61));
	nameText.setOrigin(nameText.getGlobalBounds().width / 2, nameText.getGlobalBounds().height / 2);
	nameText.setPosition(sf::Vector2f(width * 0.5, height * 0.55));

}

Gameover::~Gameover()
{

}

void Gameover::update(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp();
				break;

			case sf::Keyboard::Down:
				MoveDown();
				break;

			case sf::Keyboard::Return:
				switch (selectedItem)
				{
				case 0:
					addAndSaveScore(playername, score);
					state = MenuState;
					playername = "";
					score = 0;
					break;

				case 1:
					window.close();
					break;

				default:
					break;
				}
				break;

			case sf::Keyboard::Escape:
				window.close();
				break;
			}
			break;
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::TextEntered:
			if(event.key.code == 8 )  // check delete
			{
				if(playername.length() > 0) 
				{
					playername.pop_back(); // delete message
			    }
			}
			else if(event.key.code != 13) // Enter
			{
				playername += (char)event.key.code; // convert numbers to letters
			}
			break;
		} 
	}
	nameText.setString(playername + "_");
	nameText.setOrigin(nameText.getGlobalBounds().width / 2, nameText.getGlobalBounds().height / 2);
	nameText.setPosition(sf::Vector2f(800 * 0.5, 600 * 0.55));

	scoreText.setString("Score : " +to_string(score));
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
	scoreText.setPosition(sf::Vector2f(800 * 0.5, 600 * 0.45));
}

void Gameover::draw(sf::RenderWindow& window)
{
	window.draw(gameoverSprite);
	for (int i = 0; i < GAMEOVER_ITEMS; i++)
	{
		window.draw(gameover[i]);
	}
	window.draw(scoreText);
	window.draw(nameText);
}

void Gameover::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		gameover[selectedItem].setFillColor(sf::Color::Color(224, 250, 132));
		selectedItem--;
		gameover[selectedItem].setFillColor(sf::Color::Yellow);

	}
}

void Gameover::MoveDown()
{
	if (selectedItem + 1 < GAMEOVER_ITEMS)
	{

		gameover[selectedItem].setFillColor(sf::Color::Color(224, 250, 132));
		selectedItem++;
		gameover[selectedItem].setFillColor(sf::Color::Yellow);

	}
}
