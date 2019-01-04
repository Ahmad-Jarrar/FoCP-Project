#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


#define PI 3.14159265359
#define MAIN_MENU 10
#define CHOOSE 20
#define PLAY 30
#define GAME_END 40
#define TUTORIAL 50
#define QUIT 60

int buttonPressedOnMainMenu(sf::Vector2i);
int buttonPressedOnEndGame(sf::Vector2i);
int buttonPressedOnChoose(sf::Vector2i);
int buttonPressedOnTutorial(sf::Vector2i);

int hitTest(sf::Vector2f r1, sf::Vector2f r2);

void keepOnScreen(sf::RectangleShape * object, float window_x, float window_y);

int main()
{
	unsigned int windowMode = MAIN_MENU;
	sf::Time time;
	time.Zero;
	int score = 0, t_score;



	sf::Vector2u tempu;

	//Make Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Ghauri", sf::Style::Titlebar | sf::Style::Close);
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(1280,720));
	// User controlled Object
	sf::RectangleShape player(sf::Vector2f(90.0f, 70.0f));
	player.setOrigin(45.0f, 35.0f);
	player.setPosition(640.0f, 360.0f);
	
	// Object Textures
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("./sprites/background.png");
	background.setTexture(&backgroundTexture);
	sf::Texture player1Texture;
	player1Texture.loadFromFile("./sprites/plane1.png");
	sf::Texture player2Texture;
	player2Texture.loadFromFile("./sprites/plane2.png");
	sf::Texture player3Texture;
	player3Texture.loadFromFile("./sprites/plane3.png");
	player.setTexture(&player1Texture);
	sf::Texture missileTexture;
	missileTexture.loadFromFile("./sprites/missile.png");
	tempu = missileTexture.getSize();
	sf::Texture tutorial;
	tutorial.loadFromFile("./sprites/tutorial.png");

	//Missiles
	sf::RectangleShape missile[3];
	missile[0].setSize(sf::Vector2f(50.0f, 50.0f));
	missile[0].setTexture(&missileTexture);
	missile[0].setOrigin(25.0f, 25.0f);
	missile[0].setPosition((float)(rand() % 1000), 0.0f);

	missile[1].setSize(sf::Vector2f(50.0f, 50.0f));
	missile[1].setTexture(&missileTexture);
	missile[1].setOrigin(25.0f, 25.0f);
	missile[1].setPosition((float)(rand() % 1000), 0.0f);

	missile[2].setSize(sf::Vector2f(50.0f, 50.0f));
	missile[2].setTexture(&missileTexture);
	missile[2].setOrigin(25.0f, 25.0f);
	missile[2].setPosition(0.0f, (float)(rand() % 1000));


	//initial missile parameters
	sf::Vector2f missilePos ;
	sf::Vector2f missileVelocity;
	missileVelocity.x = 0.3f;
	missileVelocity.y = 0.0f;
	float velocity = 0.2f;
	sf::Vector2f rVelocity;


	//Buttons
	sf::RectangleShape playButton(sf::Vector2f(150.0f,100.0f));
	playButton.setOrigin(75.0f, 50.0f);
	playButton.setPosition(640.0f, 180.0f);

	sf::RectangleShape mainMenuButton(sf::Vector2f(150.0f, 100.0f));
	mainMenuButton.setOrigin(75.0f, 50.0f);
	mainMenuButton.setPosition(800.0f, 360.0f);

	sf::RectangleShape restartButton(sf::Vector2f(150.0f, 100.0f));
	restartButton.setOrigin(75.0f, 50.0f);
	restartButton.setPosition(480.0f, 360.0f);

	sf::RectangleShape tutorialButton(sf::Vector2f(150.0f, 100.0f));
	tutorialButton.setOrigin(75.0f, 50.0f);
	tutorialButton.setPosition(125.0f, 125.0f);

	sf::RectangleShape chooseButton(sf::Vector2f(150.0f, 100.0f));
	chooseButton.setOrigin(75.0f, 50.0f);
	chooseButton.setPosition(640.0f, 360.0f);

	sf::RectangleShape quitButton(sf::Vector2f(150.0f, 100.0f));
	quitButton.setOrigin(75.0f, 50.0f);
	quitButton.setPosition(640.0f, 540.0f);

	sf::RectangleShape plane1Button(sf::Vector2f(150.0f, 100.0f));
	plane1Button.setOrigin(75.0f, 50.0f);
	plane1Button.setPosition(320.0f, 360.0f);

	sf::RectangleShape plane2Button(sf::Vector2f(150.0f, 100.0f));
	plane2Button.setOrigin(75.0f, 50.0f);
	plane2Button.setPosition(640.0f, 360.0f);

	sf::RectangleShape plane3Button(sf::Vector2f(150.0f, 100.0f));
	plane3Button.setOrigin(75.0f, 50.0f);
	plane3Button.setPosition(960.0f, 360.0f);

	sf::RectangleShape backButton(sf::Vector2f(150.0f, 100.0f));
	backButton.setOrigin(75.0f, 50.0f);
	backButton.setPosition(125.0f, 125.0f);

	//Button Textures
	sf::Texture chooseTexture;
	chooseTexture.loadFromFile("./buttons/buttonChoose.png");
	sf::Texture mainMenuTexture;
	mainMenuTexture.loadFromFile("./buttons/buttonMainMenu.png");
	sf::Texture playTexture;
	playTexture.loadFromFile("./buttons/buttonPlay.png");
	sf::Texture quitTexture;
	quitTexture.loadFromFile("./buttons/buttonQuit.png");
	sf::Texture restartTexture;
	restartTexture.loadFromFile("./buttons/buttonRestart.png");
	sf::Texture tutorialTexture;
	tutorialTexture.loadFromFile("./buttons/buttonTutorial.png");
	sf::Texture backTexture;
	backTexture.loadFromFile("./buttons/buttonBack.png");

	plane1Button.setTexture(&player1Texture);
	plane2Button.setTexture(&player2Texture);
	plane3Button.setTexture(&player3Texture);

	// Assign textures to buttons
	playButton.setTexture(&playTexture);
	chooseButton.setTexture(&chooseTexture);
	mainMenuButton.setTexture(&mainMenuTexture);
	quitButton.setTexture(&quitTexture);
	restartButton.setTexture(&restartTexture);
	tutorialButton.setTexture(&tutorialTexture);
	backButton.setTexture(&backTexture);

	while (window.isOpen())
	{
		window.clear();
		window.draw(background);
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				printf("Window Height: %d\tWidth: %d\n", evnt.size.height, evnt.size.width);
				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode < 128)
				{
					printf("%c", evnt.text.unicode);
				}
			default:
				break;
			}
		}

		sf::Vector2u windowSize = window.getSize();
		sf::Vector2f windowSizef;

		sf::Vector2f playerPosition = player.getPosition();

		windowSizef.x = (float)windowSize.x;
		windowSizef.y = (float)windowSize.y;
		
		

		if (windowMode == MAIN_MENU)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				int result = buttonPressedOnMainMenu(sf::Mouse::getPosition() - window.getPosition());
				if (result == QUIT)
				{
					window.close();
				}
				else if (result > 0)
				{
					windowMode = result;
					time.Zero;
				}
			}
			window.draw(playButton);
			window.draw(chooseButton);
			window.draw(tutorialButton);
			window.draw(quitButton);
		}
		else if (windowMode == CHOOSE)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				int result = buttonPressedOnChoose(sf::Mouse::getPosition());
				if (result == 1)
				{
					
				}
				else if (result == 2)
				{

				}
				else if (result == 3)
				{

				}
				else if (result > 0)
				{
					windowMode = result;
				}
			}
			window.draw(backButton);
			window.draw(plane1Button);
			window.draw(plane2Button);
			window.draw(plane3Button);

		}
		else if (windowMode == PLAY)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				if (velocity < 1.0f)
				{
					velocity += 0.001f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{

				player.rotate(-0.5f);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				if (velocity > 0.03f)
				{
					velocity -= 0.001f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				player.rotate(0.5f);

			}

			rVelocity.x = velocity * cos(player.getRotation()* PI / 180);
			rVelocity.y = velocity * sin(player.getRotation()* PI / 180);

			keepOnScreen(&player, windowSizef.x, windowSizef.y);
			player.move(rVelocity.x, rVelocity.y);

			keepOnScreen(&missile[0], windowSizef.x, windowSizef.y);
			keepOnScreen(&missile[1], windowSizef.x, windowSizef.y);
			keepOnScreen(&missile[2], windowSizef.x, windowSizef.y);

			float distance;
			float speed[3];
			speed[0] = 0.3f;
			speed[1] = 0.45f;
			speed[2] = 0.6f;
			float max_rotation_angle = 0.5f; //can rotate only 0.1f rads/frame
			sf::Vector2f temps;
			for (size_t i = 0; i < 3; i++)
			{
				missilePos = missile[i].getPosition();
				distance = sqrt(pow(playerPosition.x - missilePos.x, 2) + pow(playerPosition.y - missilePos.y, 2));
				

				if (missilePos.x < playerPosition.x)
				{
					missile[i].move(speed[i], 0.0f);
				}
				else
				{
					missile[i].move(-speed[i], 0.0f);
				}
				if (missilePos.y < playerPosition.y)
				{
					missile[i].move(0.0f, speed[i]);
				}
				else
				{
					missile[i].move(0.0f, -speed[i]);
				}
			
				temps = missilePos + missileVelocity;

				float dot;

				dot = rVelocity.x * temps.x + rVelocity.y * temps.y;

				float angle;

				angle = acos(dot / (sqrt(temps.x * temps.x + temps.y + temps.y)) * speed[i]);

				if (angle > PI / 2)
				{
					missile[i].rotate(-max_rotation_angle);
				}
				if (angle < PI / 2)
				{
					missile[i].rotate(max_rotation_angle);
				}

				missileVelocity.x = speed[i] * cos(missile[i].getRotation()* PI / 180);
				missileVelocity.y = speed[i] * sin(missile[i].getRotation()* PI / 180);

				missile[i].move(missileVelocity.x, missileVelocity.y);

			}


			for (size_t i = 0; i < 3; i++)
			{
				if (hitTest(missile[i].getPosition(),player.getPosition()))
				{
					windowMode = GAME_END;
					score = time.asSeconds() / 2;
				}
			}
			score = (int)(time.asSeconds()) / 2;

			window.draw(player);
			window.draw(missile[0]);
			window.draw(missile[1]);
			window.draw(missile[2]);


		}
		else if (windowMode == TUTORIAL)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				int result = buttonPressedOnTutorial(sf::Mouse::getPosition());
				if (result > 0)
				{
					windowMode = result;
				}
			}

			window.clear();
			background.setTexture(&tutorial);
			window.draw(background);
			window.draw(backButton);
		}
		else if (windowMode == GAME_END)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				int result = buttonPressedOnEndGame(sf::Mouse::getPosition());
				if (result > 0)
				{
					windowMode = result;
				}
			}
			window.draw(restartButton);
			window.draw(mainMenuButton);

		}

		window.display();
	}

	return EXIT_SUCCESS;
}


void keepOnScreen(sf::RectangleShape * object, float window_x, float window_y)
{
	sf::Vector2f objectPos = object->getPosition();

	if (objectPos.x > window_x)
	{
		object->setPosition(0.0f, objectPos.y);
	}
	if (objectPos.y > window_y)
	{
		object->setPosition(objectPos.x, 0.0f);
	}
	if (objectPos.x < 0.0f)
	{
		object->setPosition(window_x, objectPos.y);
	}
	if (objectPos.y < 0.0f)
	{
		object->setPosition(objectPos.x, window_y);
	}
	return;
}

int buttonPressedOnMainMenu(sf::Vector2i mousePos)
{

	if (fabs(mousePos.x - 640.0f) < 75.0f && fabs(mousePos.y - 180.0f) < 50.0f) // Distance within Range of Play Button
	{
		return PLAY;
	}
	else if (fabs(mousePos.x - 640.0f) < 75.0f && fabs(mousePos.y - 360.0f) < 50.0f)
	{
		return CHOOSE;
	}
	else if (fabs(mousePos.x - 125.0f) < 75.0f && fabs(mousePos.y - 125.0f) < 50.0f)
	{
		return TUTORIAL;
	}
	else if (fabs(mousePos.x - 640.0f) < 75.0f && fabs(mousePos.y - 540.0f) < 50.0f)
	{
		return QUIT;
	}
	else
	{
		return 0;
	}
}

int buttonPressedOnEndGame(sf::Vector2i mousePos)
{
	if (fabs(mousePos.x - 480.0f) < 75.0f && fabs(mousePos.y - 360.0f) < 50.0f) // Distance within Range of Play Button
	{
		return PLAY;
	}
	
	else if (fabs(mousePos.x - 800.0f) < 75.0f && fabs(mousePos.y - 360.0f) < 50.0f)
	{
		return MAIN_MENU;
	}
	else
	{
		return 0;
	}
}

int buttonPressedOnChoose(sf::Vector2i mousePos)
{
	if (fabs(mousePos.x - 125.0f) < 75.0f && fabs(mousePos.y - 125.0f) < 50.0f) // Distance within Range of Play Button
	{
		return MAIN_MENU;
	}
	else if (fabs(mousePos.x - 320.0f) < 75.0f && fabs(mousePos.y - 360.0f) < 50.0f)
	{
		return MAIN_MENU;
	}
	else if (fabs(mousePos.x - 640.0f) < 75.0f && fabs(mousePos.y - 360.0f) < 50.0f)
	{
		return MAIN_MENU;
	}
	else if (fabs(mousePos.x - 960.0f) < 75.0f && fabs(mousePos.y - 360.0f) < 50.0f)
	{
		return MAIN_MENU;
	}
	else
	{
		return 0;
	}
}

int buttonPressedOnTutorial(sf::Vector2i mousePos)
{
	if (fabs(mousePos.x - 125.0f) < 75.0f && fabs(mousePos.y - 125.0f) < 50.0f) // Distance within Range of Play Button
	{
		return MAIN_MENU;//
	}
	else
	{
		return 0;
	}
}


int hitTest(sf::Vector2f r1, sf::Vector2f r2)
{
	return ((r1.x + 20 >= r2.x) && (r1.x <= r2.x + 20) && (r1.y + 20 >= r2.y) && (r1.y <= r2.y + 20));
}