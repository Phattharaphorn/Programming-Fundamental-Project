#include "Score.h"

Score::Score(float width, float height)
{
	this->size = sf::Vector2f(800.0f, 600.0f);
	selectedItem = 0;

	scoreTexture.loadFromFile("score.jpg");
	scoreSprite.setTexture(scoreTexture);

	if (!font.loadFromFile("SDfont.ttf"))
	{
		//handle error
	}
	
	score[0].setFont(font);
	score[0].setCharacterSize(60);
	score[0].setFillColor(sf::Color::Yellow);
	score[0].setString("Back");
	score[0].setOrigin(score[0].getGlobalBounds().width / 2, score[0].getGlobalBounds().height / 2);
	score[0].setPosition(sf::Vector2f(width / 2.6, height / (SCORE_ITEMS + 1) * 2.5));

	score[1].setFont(font);
	score[1].setCharacterSize(60);
	score[1].setFillColor(sf::Color::Black);
	score[1].setString("Exit");
	score[1].setOrigin(score[1].getGlobalBounds().width / 2, score[1].getGlobalBounds().height / 2);
	score[1].setPosition(sf::Vector2f(width / 1.58, height / (SCORE_ITEMS + 1.60) * 3));

	readScoreFile();

	for (int i = 0; i < 5; i++)
	{
		nameTexts[i].setFont(font);
		nameTexts[i].setCharacterSize(50);
		nameTexts[i].setFillColor(sf::Color::White);
		nameTexts[i].setPosition(Vector2f(200, 150 + (60 * i)));
		
		scoreTexts[i].setFont(font);
		scoreTexts[i].setCharacterSize(50);
		scoreTexts[i].setFillColor(sf::Color::White);
		scoreTexts[i].setOrigin(Vector2f(scoreTexts[i].getGlobalBounds().width, 0));
		scoreTexts[i].setPosition(Vector2f(600, 150 + (60 * i)));
	}
}

Score::~Score()
{

}
// โหลดข้อมูล
void Score::loadScore()
{
	readScoreFile();
	for (int i = 0; i < 5; i++)
	{
		nameTexts[i].setString(to_string(i + 1) + ". " + scoredata[i].name); // ตั้งชื่อ

		scoreTexts[i].setString(to_string(scoredata[i].score));
		scoreTexts[i].setOrigin(Vector2f(scoreTexts[i].getGlobalBounds().width, 0));
		scoreTexts[i].setPosition(Vector2f(600, 150 + (60 * i)));
	}
}

void Score::update(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code) {
			case sf::Keyboard::Left:
				MoveLeft();
				break;

			case sf::Keyboard::Right:
				MoveRight();
				break;

			case sf::Keyboard::Return:
				switch (selectedItem)
				{
				case 0:
					state = MenuState;
					break;

				case 1:
					window.close();					
					break;

				default:
					break;
				}
				break;
			}
			break;

		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Score::draw(sf::RenderWindow& window)
{
	window.draw(scoreSprite);
	for (int i = 0; i < SCORE_ITEMS; i++)
	{
		window.draw(score[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		window.draw(nameTexts[i]);
		window.draw(scoreTexts[i]);
	}
}

void Score::MoveLeft()
{
	if (selectedItem - 1 >= 0)
	{
		score[selectedItem].setFillColor(sf::Color::Black);
		selectedItem--;
		score[selectedItem].setFillColor(sf::Color::Yellow);

	}
}

void Score::MoveRight()
{
	if (selectedItem + 1 < SCORE_ITEMS)
	{

		score[selectedItem].setFillColor(sf::Color::Black);
		selectedItem++;
		score[selectedItem].setFillColor(sf::Color::Yellow);

	}
}
