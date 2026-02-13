#pragma once
#include "Tilemap.h"

class TilemapUI
{
private:
	Tilemap Tilemap;
	
	std::string  m_FilepathCurrentLevel;
	std::string  m_FilepathTilemap;

	const sf::Texture* m_TextureTilemap;

public:
	TilemapUI();

	void loadTilemapTexture(std::string filepathTilemap);
	void loadExistingLevel(std::string filepathLevel);
	
	void saveCurrentLevel();

	void render();
};

