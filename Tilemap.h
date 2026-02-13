#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class Tilemap : public sf::Drawable
{
private:
    const sf::Texture& m_Texture;
    sf::VertexArray m_Vertices;
    
    std::vector<std::vector<int>> m_ArrayLevel;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.texture = &m_Texture;
        target.draw(m_Vertices, states);
    }

public:	
    Tilemap(const sf::Texture& texture, std::string levelFilePath);

    std::vector<std::vector<int>> loadLevel(std::string levelFilePath);
};

