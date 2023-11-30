#include "Game.h"
#include "Menu.h"
#include "Gameover.h"
#include "Score.h"

int state = MenuState;
ScoreData scoredata[6];  

int main()
{
    RenderWindow window(VideoMode(800, 600), "Game", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    srand(time(NULL));

    Clock clock;
    float deltaTime = 0;

    Game game(&window);
    Score scoreScene(800, 600);
    Menu menu(&window, &scoreScene);
    Gameover over(800, 600);
   
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (state == MenuState)
        {
            menu.update();
        }
        else if (state == GameState)
        {
            game.update(deltaTime);
        }
        else if (state == OverState)
        {
            over.update(window);
        }
        else if (state == ScoreState)
        {
            scoreScene.update(window);
        }
        window.clear();
        if (state == MenuState)
        {
            menu.draw();
        }
        else if (state == GameState)
        {
            game.render();
        }
        else if (state == OverState)
        {
            over.draw(window);
        }
        else if (state == ScoreState)
        {
            scoreScene.draw(window);
        }
        window.display();
    }
    return 0;
}