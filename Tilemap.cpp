#include "Tilemap.h"

Tilemap::Tilemap(const sf::Texture& texture, std::string levelFilePath) :
	m_Texture(texture)
{	
	m_FillTile.m_Id = 0;
}

void Tilemap::setLevelSize(sf::Vector2u levelSize)
{
	m_LevelSize = levelSize;

	m_ArrayLevel.resize(static_cast<size_t>(levelSize.x) * levelSize.y);
	std::fill(m_ArrayLevel.begin(), m_ArrayLevel.end(), m_FillTile);
}

void Tilemap::setFillTile(Tile fillTile)
{
	m_FillTile = fillTile;
}

void Tilemap::placeTile(sf::Vector2i gridPosition, Tile tile)
{
	if (gridPosition.x > m_LevelSize.x || gridPosition.x < 0 ||
		gridPosition.y > m_LevelSize.y || gridPosition.y < 0)
	{
		return;
	}

	m_ArrayLevel[gridPosition.x + static_cast<size_t>(gridPosition.y) * m_LevelSize.x] = tile;
}

void Tilemap::removeTile(sf::Vector2i gridPosition)
{
	if (gridPosition.x > m_LevelSize.x || gridPosition.x < 0 ||
		gridPosition.y > m_LevelSize.y || gridPosition.y < 0)
	{
		return;
	}

	if (gridPosition.x == m_LevelSize.x)
	{
		sf::Vector2u toLevelSize = m_LevelSize;
		toLevelSize.x--;
		setLevelSize(toLevelSize);
	}
	if (gridPosition.y == m_LevelSize.y)
	{
		sf::Vector2u toLevelSize = m_LevelSize;
		toLevelSize.y--;
		setLevelSize(toLevelSize);
	}

	m_ArrayLevel[gridPosition.x + static_cast<size_t>(gridPosition.y) * m_LevelSize.x] = m_FillTile;
}
