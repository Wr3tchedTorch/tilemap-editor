#include "Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/System/Time.hpp>
#include <iostream>

void Engine::update(float delta)
{		
	ImGui::SFML::Update(m_Window, sf::seconds(delta));

	sf::Vector2i screenMousePosition = sf::Mouse::getPosition();
	sf::Vector2f globalMousePosition = m_Window.mapPixelToCoords(screenMousePosition, m_MainView);

	std::cout << m_Tilemap.levelToString() << "\n";
}