#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Ghauri",sf::Style::Default);
	sf::RectangleShape player(sf::Vector2f(100.0f,100.0f));
	player.setFillColor(sf::Color::Red);
	player.setOrigin(50.0f, 50.0f);
	player.setPosition(200.0f, 200.0f);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("");


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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player.move(0.0f,-0.05f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			player.move(-0.05f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player.move(0.0f, 0.05f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			player.move(0.05f, 0.0f);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x,(float)mousePos.y);
		}




		
		window.clear(sf::Color::Blue);
		window.draw(player);
		window.display();
	}

	return 0;
}