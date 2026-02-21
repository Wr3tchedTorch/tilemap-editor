#include "Tilemap.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <string>
#include <vector>
#include "Tile.h"

Tilemap::Tilemap(const sf::Texture& texture, std::string levelFilePath, sf::Vector2u tileSize, sf::Vector2u tilemapSize) :
	m_Texture(texture)
{	
	m_FillTile.Id	= -1;
	m_FilepathLevel = levelFilePath;
	m_TilemapSize   = tilemapSize;

	m_TileSize = tileSize;

	loadLevelFromDisk(m_FilepathLevel);
	updateVertices();
}

void Tilemap::increaseLevelSize(sf::Vector2u levelSize)
{
	if (levelSize.x < m_LevelSize.x || levelSize.y < m_LevelSize.y)
	{
		return;
	}

	size_t newSize = static_cast<size_t>(levelSize.x) * levelSize.y;

	std::vector<Tile> toArrayLevel;
	toArrayLevel.resize(newSize, m_FillTile); 

	for (int y = 0; y < m_LevelSize.y; ++y)
	{
		for (int x = 0; x < m_LevelSize.x; ++x)
		{
			Tile tile = m_ArrayLevel[x + static_cast<size_t>(y) * m_LevelSize.x];			
			if (tile.Id == m_FillTile.Id)
			{
				continue;
			}
			toArrayLevel[x + static_cast<size_t>(y) * levelSize.x] = tile;
		}
	}

	m_ArrayLevel = toArrayLevel;
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

void Tilemap::setTilemapSize(sf::Vector2u tilemapSize)
{
	m_TilemapSize = tilemapSize;
}

void Tilemap::removeTiles(sf::IntRect positions)
{
	int startX = positions.position.x;
	int endX   = positions.position.x + positions.size.x;

	int startY = positions.position.y;
	int endY   = positions.position.y + positions.size.y;
	
	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			removeTile({x, y});
		}
	}
}

void Tilemap::placeTiles(sf::IntRect positions, Tile tile)
{
	int startX = positions.position.x;
	int endX = positions.position.x + positions.size.x;

	int startY = positions.position.y;
	int endY = positions.position.y + positions.size.y;

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			placeTile({ x, y }, tile);
		}
	}
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
		increaseLevelSize(toLevelSize);
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

Tile Tilemap::getTile(sf::Vector2i gridPosition)
{
	assert(gridPosition.x >= 0 && gridPosition.x < m_LevelSize.x && gridPosition.y >= 0 && gridPosition.y < m_LevelSize.y);

	Tile tile = m_ArrayLevel[gridPosition.x + static_cast<size_t>(gridPosition.y) * m_LevelSize.x];

	tile.GlobalPosition = sf::Vector2f(gridPosition);
	tile.GlobalPosition.x *= m_TileSize.x;
	tile.GlobalPosition.y *= m_TileSize.y;

	return tile;
}

std::string Tilemap::levelToString()
{
	std::string result;
	for (int i = 0; i < m_ArrayLevel.size(); ++i)
	{
		std::string id = std::to_string(m_ArrayLevel[i].Id);
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
