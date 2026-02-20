#include "Engine.h"
#include "imgui-SFML.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

void Engine::update(float delta)
{		
	ImGui::SFML::Update(m_Window, sf::seconds(delta));

	sf::Vector2i screenMousePosition = sf::Mouse::getPosition();
	sf::Vector2f globalMousePosition = m_Window.mapPixelToCoords(screenMousePosition, m_MainView);
	m_TilemapUI.update(globalMousePosition);
}