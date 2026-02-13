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
		if (const auto& keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			{
				m_Window.close();
			}
		}
	}
}