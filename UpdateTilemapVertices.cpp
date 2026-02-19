#include "Tilemap.h"

void Tilemap::updateVertices()
{
	m_Vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
	m_Vertices.resize(static_cast<size_t>(m_LevelSize.x) * m_LevelSize.y * VERTICES_PER_TILE);

	size_t currentVertex = 0;
	for (int y = 0; y < m_LevelSize.y; ++y)
	{
		for (int x = 0; x < m_LevelSize.x; ++x)
		{
			int TILE_INDEX = m_ArrayLevel[x + static_cast<size_t>(y) * m_LevelSize.x].Id;

			if (TILE_INDEX == -1)
			{
				for (int i = 0; i < VERTICES_PER_TILE; ++i)
				{
					m_Vertices[currentVertex + i].position = {0, 0};
					m_Vertices[currentVertex + i].color	   = sf::Color::Red;
				}
				currentVertex += VERTICES_PER_TILE;
				continue;
			}

			float top    = y * m_TileSize.y;
			float left   = x * m_TileSize.x;
			float bottom = top  + m_TileSize.y;
			float right  = left + m_TileSize.x;

			m_Vertices[currentVertex + 0].position = { left,  top };
			m_Vertices[currentVertex + 1].position = { left,  bottom };
			m_Vertices[currentVertex + 2].position = { right, top };

			m_Vertices[currentVertex + 3].position = { right, top };
			m_Vertices[currentVertex + 4].position = { right, bottom };
			m_Vertices[currentVertex + 5].position = { left,  bottom };

			int textureX = TILE_INDEX % m_TilemapSize.x;
			int textureY = TILE_INDEX / m_TilemapSize.x;

			float textureTop    = textureY * m_TileSize.y;
			float textureLeft   = textureX * m_TileSize.x;
			float textureBottom = textureTop  + m_TileSize.y;
			float textureRight  = textureLeft + m_TileSize.x;

			m_Vertices[currentVertex + 0].texCoords = { textureLeft,  textureTop };
			m_Vertices[currentVertex + 1].texCoords = { textureLeft,  textureBottom };
			m_Vertices[currentVertex + 2].texCoords = { textureRight, textureTop };

			m_Vertices[currentVertex + 3].texCoords = { textureRight, textureTop };
			m_Vertices[currentVertex + 4].texCoords = { textureRight, textureBottom };
			m_Vertices[currentVertex + 5].texCoords = { textureLeft,  textureBottom };

			currentVertex += VERTICES_PER_TILE;
		}
	}
}