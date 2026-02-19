#include "Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "TilemapUI.h"

#include <SFML/Graphics/RectangleShape.hpp>

void Engine::draw()
{
	m_Window.clear(m_ColorBackground);			

	m_Window.setView(m_MainView);

	m_Window.draw(m_Tilemap);
	
	ImGui::SFML::Render(m_Window);
	m_Window.display();
}