#include "TextureHolder.h"

TextureHolder* TextureHolder::m_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_Instance == nullptr);
	m_Instance = this;
}

const sf::Texture& TextureHolder::GetTexture(const std::string& filepath)
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
