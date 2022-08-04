#include <iostream>
#include "SFML/Graphics.hpp"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "No arguments provided!\n";
		return -1;
	}

	sf::Texture texture;
	if (!texture.loadFromFile(argv[1]))
	{
		std::cout << "Image \"" << argv[1] << "\" could not be loaded!\n";
		return -1;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sf::FloatRect rect = sprite.getLocalBounds();
	float scale = 1.0f;

	float argScale = 1.0f;
	if (argc > 2)
	{
		for (int i = 2; i < argc; i++)
		{
			std::string arg = argv[i];
			switch (arg[0])
			{
			case 's':
				argScale = std::stof(arg.erase(0, 2));
				break;

			case 'c':
				switch (arg[2])
				{
				case 'r':
					sprite.setColor(sf::Color(
						std::stoi(arg.erase(0,4)), 
						sprite.getColor().g, 
						sprite.getColor().b, 
						sprite.getColor().a));
					break;

				case 'g':
					sprite.setColor(sf::Color(
						sprite.getColor().r,
						std::stoi(arg.erase(0, 4)),
						sprite.getColor().b,
						sprite.getColor().a));
					break;

				case 'b':
					sprite.setColor(sf::Color(
						sprite.getColor().r,
						sprite.getColor().g,
						std::stoi(arg.erase(0, 4)),
						sprite.getColor().a));
					break;

				case 'a':
					sprite.setColor(sf::Color(
						sprite.getColor().r,
						sprite.getColor().g,
						sprite.getColor().b,
						std::stoi(arg.erase(0, 4))));
					break;

				default:
					std::cout << "No sub-argument '" << arg[2] << "' exists for argument 'c'!";
					return -1;
				}
				break;

			case 'r':
				switch (arg[2])
				{
				case 'l':
					sprite.setTextureRect(sf::IntRect(
						std::stoi(arg.erase(0, 4)),
						sprite.getTextureRect().top,
						sprite.getTextureRect().width,
						sprite.getTextureRect().height));
					break;

				case 't':
					sprite.setTextureRect(sf::IntRect(
						sprite.getTextureRect().left,
						std::stoi(arg.erase(0, 4)),
						sprite.getTextureRect().width,
						sprite.getTextureRect().height));
					break;

				case 'w':
					sprite.setTextureRect(sf::IntRect(
						sprite.getTextureRect().left,
						sprite.getTextureRect().top,
						std::stoi(arg.erase(0, 4)),
						sprite.getTextureRect().height));
					break;

				case 'h':
					sprite.setTextureRect(sf::IntRect(
						sprite.getTextureRect().left,
						sprite.getTextureRect().top,
						sprite.getTextureRect().width,
						std::stoi(arg.erase(0, 4))));
					break;

				default:
					std::cout << "No sub-argument '" << arg[2] << "' exists for argument 'r'!";
					return -1;
				}
				break;

			default:
				std::cout << "No argument '" << arg[0] << "' exists!";
				return -1;
			}
		}
	}

	if (rect.width < 120)
	{
		scale = 120.0f / rect.width;
	}
	sprite.setScale(scale * argScale, scale * argScale);

	sf::RenderWindow window(sf::VideoMode(rect.width * scale * argScale, rect.height * scale * argScale), "SFML Image Viewer");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				std::cout << "Window closed.";
			}
		}
		window.draw(sprite);
		window.display();
	}
    return 0;
}