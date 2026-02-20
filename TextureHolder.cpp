#include "TextureHolder.h"
#include <cassert>
#include <string>
#include <SFML/Graphics/Texture.hpp>

TextureHolder* TextureHolder::m_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_Instance == nullptr);
	m_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(const std::string& filepath)
{
	auto& map = m_Instance->m_Textures;

	auto search = map.find(filepath);

	if (search == map.end())
	{
		map[filepath].loadFromFile(filepath);
		return map[filepath];
	}

	return search->second;
}
