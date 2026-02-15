#include "Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"

Engine::Engine() : m_TilemapUI(m_Window, "foo.png", "foo.dat")
{
	m_ColorBackground = sf::Color::Black;

	m_TilemapUI.loadTilemap("graphics/tilemap.png", 16);
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
