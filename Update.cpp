#include "Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/System/Time.hpp>

void Engine::update(float delta)
{		
	ImGui::SFML::Update(m_Window, sf::seconds(delta));
}