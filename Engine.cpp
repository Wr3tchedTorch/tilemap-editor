#include "Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"

Engine::Engine() :
	m_Tilemap(TextureHolder::GetTexture("graphics/tilemap.png"), "levels/test.dat", {16, 16})
{
	m_ColorBackground = sf::Color::Black;	
}

void Engine::run()
{
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	m_Window.create(vm, "Tilemap editor by Eric", sf::State::Fullscreen);
	ImGui::SFML::Init(m_Window);

	m_MainView.setSize(sf::Vector2f(vm.size));

	sf::Vector2f vmHalfSize(vm.size);
	vmHalfSize.x /= 2;
	vmHalfSize.y /= 2;
	m_MainView.setCenter(vmHalfSize);

	sf::Clock deltaClock;
	while (m_Window.isOpen())
	{
		sf::Time deltaTime = deltaClock.restart();
		float delta = deltaTime.asSeconds();

		input();
		update(delta);
		draw();
	}
}

void Engine::setBackgroundColor(sf::Color toColor)
{
	m_ColorBackground = toColor;
}
