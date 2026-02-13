#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class TextureHolder
{
private:
	std::unordered_map<std::string, sf::Texture> m_Textures;

	static TextureHolder* m_Instance;

public:
	TextureHolder();

	static const sf::Texture& GetTexture(const std::string& filepath);
};

