#pragma once
#include "Tilemap.h"
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class TilemapUI
{
private:
	std::string  m_FilepathCurrentLevel = "";
	std::string  m_FilepathTilemap		= "";

	const sf::Texture* m_TextureTilemap = nullptr;

	sf::Vector2u m_TileSize;
	sf::Vector2u m_TilemapSize;

	sf::Vector2i m_GridMousePosition;
	int m_SelectedTileIndex = 0;

	sf::IntRect  m_SelectedGridTiles;

	std::vector<std::shared_ptr<Tilemap>> m_MapLayers;

	int  m_SelectedLayerIndex = 0;
	bool m_IsMouseDragValid   = false;

	sf::RenderWindow& m_Window;

	void drawTilemapUI();
	void updateSelectedGridSize();

public:
	TilemapUI(sf::RenderWindow& window);

	void leftMouseButtonPressed();
	void rightMouseButtonPressed();

	void leftMouseButtonReleased();
	void rightMouseButtonReleased();

	void placeTiles(sf::FloatRect globalMousePosition);
	void removeTiles(sf::FloatRect globalMousePosition);

	void loadLayerFromDisk(std::string filepathLevel);
	void addLayer(std::string filepathLayer);
	void removeLayer(int index);
	void switchLayers(int index, int other);

	void loadTilemap(std::string filepathTilemap, sf::Vector2u tileSize, sf::Vector2u tilemapSize);
	void saveCurrentLevel();
	void closeCurrentLevel();

	void update(sf::Vector2f mapWorldPosition);

	void render();
	void drawTilemap();
	std::vector<std::shared_ptr<Tilemap>> getMapLayers();
};

