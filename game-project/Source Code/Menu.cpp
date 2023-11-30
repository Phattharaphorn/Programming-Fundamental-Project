#include "Menu.h"

Menu::Menu(RenderWindow* window, Score* ss)
{
	this->window = window;
	scoreScene = ss;
	float width = window->getSize().x;
	float height = window->getSize().y;
	this->size = sf::Vector2f(800.0f, 600.0f);
	backgroundTexture.loadFromFile("background9.jpg");
	background.setTexture(backgroundTexture);

	if (!font.loadFromFile("SDfont.ttf"))
	{

	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(80);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Play");
	// menu[0].setOrigin(menu[0].getGlobalBounds().width / 2, menu[0].getGlobalBounds().height / 2);
	menu[0].setOrigin(0, menu[0].getGlobalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(80, height / 2));

	menu[1].setFont(font);
	menu[1].setCharacterSize(80);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("Score");
	menu[1].setOrigin(menu[1].getGlobalBounds().width / 2, menu[1].getGlobalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / 2));

	menu[2].setFont(font);
	menu[2].setCharacterSize(80);
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setString("Exit");
	// menu[2].setOrigin(menu[2].getGlobalBounds().width / 2, menu[2].getGlobalBounds().height / 2);
	menu[2].setOrigin(menu[2].getGlobalBounds().width, menu[0].getGlobalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width - 80, (height / 2) + 5));

	selectedItem = 0;
}

Menu::~Menu()
{

}

void Menu::draw()
{
	window->draw(background);
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window->draw(menu[i]);
	}
}

void Menu::update()
{
	Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				MoveLeft();
				break;

			case sf::Keyboard::Right:
				MoveRight();
				break;

			case sf::Keyboard::Return:
				switch (GetPressedItem())
				{
				case 0:
					state = GameState;
					break;

				case 1:
					state = ScoreState;
					scoreScene->loadScore();
					break;

				case 2:
					window->close();
					break;

				default:
					break;
				}
				break;
			}
			break;

		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}

void Menu::MoveLeft()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::Black);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Yellow);

	}

}

void Menu::MoveRight()
{
	if (selectedItem + 1 < MAX_ITEMS)
	{

		menu[selectedItem].setFillColor(sf::Color::Black);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Yellow);

	}

}
