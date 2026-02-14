#include "Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"

void Engine::input()
{
	while (const std::optional event = m_Window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(m_Window, *event);

		if (event->is<sf::Event::Closed>())
		{
			m_Window.close();
		}
		else if (const auto& keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			{
				m_Window.close();
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
			{
				m_MainView.zoom(0.9f);
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
			{
				m_MainView.zoom(1.1f);
			}

			if (keyPressed->scancode == sf::Keyboard::Scancode::W)
			{
				m_MainView.move({0, -20});
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
			{
				m_MainView.move({ 0, 20 });
			}

			if (keyPressed->scancode == sf::Keyboard::Scancode::A)
			{
				m_MainView.move({ -20, 0 });
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
			{
				m_MainView.move({ 20, 0 });
			}
		}
	}
}