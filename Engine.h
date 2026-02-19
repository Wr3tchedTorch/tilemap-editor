#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include "TextureHolder.h"
#include "TilemapUI.h"

class Engine
{
private:
	TextureHolder m_TextureHolderSingleton;

	Tilemap m_Tilemap;

	sf::RenderWindow m_Window;
	sf::View  m_MainView;
	sf::Color m_ColorBackground;

	void input();
	void update(float delta);
	void draw();

public:
	Engine();
	void run();

	void setBackgroundColor(sf::Color toColor);
};

