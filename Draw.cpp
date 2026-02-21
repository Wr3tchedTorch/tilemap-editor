#include "Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "TilemapUI.h"

#include <SFML/Graphics/RectangleShape.hpp>

void Engine::draw()
{
	m_Window.clear(m_ColorBackground);		

	ImGui::Begin("Tilemap editor by Eric!");

	m_TilemapUI.render();

	ImGui::End();

	m_Window.setView(m_MainView);

	m_TilemapUI.drawTilemap();

	ImGui::SFML::Render(m_Window);
	m_Window.display();
}