#pragma once
#include "Tilemap.h"
#include <SFML/Graphics/RenderWindow.hpp>

class TilemapUI
{
private:
	std::string  m_FilepathCurrentLevel;
	std::string  m_FilepathTilemap;

	const sf::Texture* m_TextureTilemap;

	int m_TileSize;
	sf::Vector2i m_TilemapSize;
	sf::Vector2i m_GridMousePosition;
	sf::Vector2i m_SelectedTile;

	const sf::Window& m_Window;

	void drawTilemapUI();

public:
	TilemapUI(const sf::Window& window, std::string filepathTilemap, std::string filepathLevel);

	void leftMouseButtonPressed();
	void rightMouseButtonPressed();

	void placeTiles(sf::FloatRect globalMousePosition);
	void removeTiles(sf::FloatRect globalMousePosition);

	void loadTilemap(std::string filepathTilemap, int tileSize);	
	void loadExistingLevel(std::string filepathLevel);	
	void saveCurrentLevel();

	void update(sf::Vector2f mapWorldPosition);

	void render();
};

