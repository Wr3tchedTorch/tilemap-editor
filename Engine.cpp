#include "Engine.h"
#include "imgui.h"
#include "imgui-SFML.h"

Engine::Engine() :
	m_Tilemap(TextureHolder::GetTexture("graphics/tilemap.png"), "levels/test.dat", { 16, 16 }, { 18, 13 })
{
	m_ColorBackground = sf::Color::Black;	

	//m_Tilemap.setFillTile(Tile{ 1 });
	//m_Tilemap.placeTile({ 7, 7 }, Tile { 39 });

	//m_Tilemap.saveLevelToDisk();
}

void Engine::run()
{
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	m_Window.create(vm, "Tilemap editor by Eric", sf::State::Fullscreen);
	ImGui::SFML::Init(m_Window);

	m_MainView.setSize(sf::Vector2f(vm.size));
	m_MainView.zoom(0.5f);

	sf::Vector2f vmHalfSize(vm.size);
	vmHalfSize.x /= 2;
	vmHalfSize.y /= 2;
	m_MainView.setCenter({
		vmHalfSize.x - m_MainView.getSize().x / 2,
		vmHalfSize.y - m_MainView.getSize().y / 2
	});

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
