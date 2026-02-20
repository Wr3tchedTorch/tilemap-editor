#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>
#include "Tile.h"

class Tilemap : public sf::Drawable
{
private:
    const int VERTICES_PER_TILE = 6;

    const sf::Texture& m_Texture;
    sf::VertexArray m_Vertices;
    
    std::vector<Tile> m_ArrayLevel;

    sf::Vector2u m_LevelSize;
    sf::Vector2u m_TileSize;
    sf::Vector2u m_TilemapSize;

    Tile m_FillTile;

    std::string m_FilepathLevel;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.texture = &m_Texture;
        target.draw(m_Vertices, states);
    }

    void updateVertices();
    void trimTilemap();
    void increaseLevelSize(sf::Vector2u levelSize);

public:	
    Tilemap(const sf::Texture& texture, std::string levelFilePath, sf::Vector2u tileSize, sf::Vector2u tilemapSize);
    
    void setFillTile(Tile fillTile);
    void setTileSize(sf::Vector2u tileSize);
    void setTilemapSize(sf::Vector2u tilemapSize);
    
    void removeTiles(sf::IntRect positions);
    void placeTiles(sf::IntRect positions, Tile tile);

    void placeTile(sf::Vector2i gridPosition, Tile tile);
    void removeTile(sf::Vector2i gridPosition);
    Tile getTile(sf::Vector2i gridPosition);

    void loadLevelFromDisk(std::string filepathLevel);
    void saveLevelToDisk();

	std::string getLevelFilepath() const { return m_FilepathLevel; }
    
    std::string levelToString();
};

