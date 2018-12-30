#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


#define PI 3.14159265359

void keepOnScreen(sf::RectangleShape * object, float window_x, float window_y);

int main()
{
	sf::Vector2u tempu;
	

	sf::RenderWindow window(sf::VideoMode(1280,720), "Ghauri",sf::Style::Default);
	sf::RectangleShape background;
	
	sf::RectangleShape player(sf::Vector2f(90.0f,70.0f));
	player.setOrigin(45.0f, 35.0f);
	player.setPosition(640.0f, 360.0f);

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background.png");

	sf::Texture playerTexture;
	playerTexture.loadFromFile("f-22.png");
	player.setTexture(&playerTexture);
	sf::Texture missileTexture;
	missileTexture.loadFromFile("missile1.png");
	tempu = missileTexture.getSize();
	
	sf::RectangleShape missile[5];
	missile[1].setSize(sf::Vector2f(50.0f,50.0f));
	missile[1].setTexture(&missileTexture);
	missile[1].setOrigin(25.0f,25.0f);
	missile[1].setPosition((float)(rand() % 1000),0.0f);
	
	sf::Vector2f missilePos = missile[1].getPosition();
	sf::Vector2f missileVelocity;
	missileVelocity.x = 0.5f;
	missileVelocity.y = 0.0f;
	float velocity = 0.2f;
	sf::Vector2f rVelocity;

	while (window.isOpen())
	{
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				printf("Window Height: %d\tWidth: %d\n",evnt.size.height, evnt.size.width);
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
		background.setSize(windowSizef);
		background.setTexture(&backgroundTexture);
		
		


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

		keepOnScreen(&missile[1],windowSizef.x, windowSizef.y);
		
		float speed = 0.6f;
		float max_rotation_angle = 0.5f; //can rotate only 0.1f rads/frame

		sf::Vector2f delta;
		delta = rVelocity - missileVelocity;

		float dot;

		 dot = rVelocity.x * missileVelocity.x + rVelocity.y * missileVelocity.y;

		 float angle;

		 angle = acos(dot / velocity * speed);
		
		if (angle > PI / 2)
		{
			missile[1].rotate(-max_rotation_angle);
		}
		if (angle < PI / 2)
		{
			missile[1].rotate(max_rotation_angle);
		}
		
		missileVelocity.x = speed * cos(missile[1].getRotation()* PI / 180);
		missileVelocity.y = speed * sin(missile[1].getRotation()* PI / 180);
		
		missile[1].move(missileVelocity.x, missileVelocity.y);
		printf("angle: %f\t x: %f\t y:%f\n", angle, playerPosition.x, playerPosition.y);
		window.clear();

		window.draw(background);
		window.draw(player);
		window.draw(missile[1]);
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