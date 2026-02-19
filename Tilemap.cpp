#include "Tilemap.h"
#include <iostream>
#include <fstream>

Tilemap::Tilemap(const sf::Texture& texture, std::string levelFilePath, sf::Vector2u tileSize, sf::Vector2u tilemapSize) :
	m_Texture(texture)
{	
	m_FillTile.m_Id = 0;
	m_FilepathLevel = levelFilePath;
	m_TilemapSize   = tilemapSize;

	m_TileSize = tileSize;

	loadLevelFromDisk(m_FilepathLevel);
	updateVertices();
}

void Tilemap::setLevelSize(sf::Vector2u levelSize)
{
	size_t newSize = static_cast<size_t>(levelSize.x) * levelSize.y;

	m_ArrayLevel.resize(newSize, m_FillTile);
	m_LevelSize = levelSize;

	updateVertices();
}

void Tilemap::setFillTile(Tile fillTile)
{
	m_FillTile = fillTile;
}

void Tilemap::setTileSize(sf::Vector2u tileSize)
{
	m_TileSize = tileSize;
}

void Tilemap::placeTile(sf::Vector2i gridPosition, Tile tile)
{
	if (gridPosition.x < 0 || gridPosition.y < 0)
	{
		return;
	}

	bool isXOutOfBounds = gridPosition.x >= m_LevelSize.x;
	bool isYOutOfBounds = gridPosition.y >= m_LevelSize.y;

	if (isXOutOfBounds || isYOutOfBounds)
	{
		sf::Vector2u toLevelSize = m_LevelSize;
		toLevelSize.x = isXOutOfBounds ? gridPosition.x + 1 : toLevelSize.x;
		toLevelSize.y = isYOutOfBounds ? gridPosition.y + 1 : toLevelSize.y;
		setLevelSize(toLevelSize);
	}

	m_ArrayLevel[gridPosition.x + static_cast<size_t>(gridPosition.y) * m_LevelSize.x] = tile;
	updateVertices();
}

void Tilemap::removeTile(sf::Vector2i gridPosition)
{
	if (gridPosition.x > m_LevelSize.x || gridPosition.x < 0 ||
		gridPosition.y > m_LevelSize.y || gridPosition.y < 0)
	{
		return;
	}

	m_ArrayLevel[gridPosition.x + static_cast<size_t>(gridPosition.y) * m_LevelSize.x] = m_FillTile;
	updateVertices();
}

std::string Tilemap::levelToString()
{
	std::string result;
	for (int i = 0; i < m_ArrayLevel.size(); ++i)
	{
		std::string id = std::to_string(m_ArrayLevel[i].m_Id);
		result += id;

		if (i < m_ArrayLevel.size() - 1)
		{
			result += ",";
		}

		if (i != 0 && (i + 1) % m_LevelSize.x == 0)
		{
			result += "\n";
		}
	}
	return result;
}
