// TilemapEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main()
{
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();

	sf::RenderWindow window(vm, "Tilemap Editor by Eric");
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				{
					window.close();
				}
			}
		}

		sf::Time deltaTime = deltaClock.restart();
		float delta = deltaTime.asSeconds();

		ImGui::SFML::Update(window, deltaTime);




		window.clear(sf::Color::Blue);

		ImGui::SFML::Render(window);

		window.display();
	}

	return 0;
}
