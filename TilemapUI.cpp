#include "TilemapUI.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "TextureHolder.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

TilemapUI::TilemapUI(const sf::Window& window) : m_Window(window)
{
}

void TilemapUI::loadTilemap(std::string filepathTilemap, int tileSize)
{
	m_TextureTilemap = &TextureHolder::GetTexture(filepathTilemap);
	m_FilepathTilemap = filepathTilemap;

	m_TileSize	  = tileSize;
	m_TilemapSize = {
		static_cast<int>(m_TextureTilemap->getSize().x) / m_TileSize,
		static_cast<int>(m_TextureTilemap->getSize().y) / m_TileSize
	};	
}

void TilemapUI::update(sf::Vector2f mapWorldPosition)
{	
	m_GridMousePosition.x = mapWorldPosition.x / m_TileSize;
	m_GridMousePosition.y = mapWorldPosition.y / m_TileSize;
}

void TilemapUI::render()
{
	ImGui::Text(std::format("texture file: {}", m_FilepathTilemap).c_str());
	ImGui::Text(std::format("Tilemap size: (width: {}, height: {})", m_TilemapSize.x, m_TilemapSize.y).c_str());

	ImGui::Text(std::format("grid mouse position: (x: {}, y: {})", m_GridMousePosition.x, m_GridMousePosition.y).c_str());	

	sf::Sprite iconsSprite(*m_TextureTilemap);

	float tileSizeFloat = static_cast<float>(m_TileSize);
	
	int width  = m_TilemapSize.x;
	int height = m_TilemapSize.y;

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			ImGui::PushID(y * width + x);

			int left   = x * m_TileSize;
			int top    = y * m_TileSize;

			iconsSprite.setTextureRect({ {left, top}, {m_TileSize, m_TileSize} });

			std::string buttonId = std::format("tile_button{}{}", x, y);
			bool pressed = ImGui::ImageButton(buttonId.c_str(), iconsSprite, { 32, 32 });

			if (pressed)
			{
				std::cout << std::format("Tile: (x: {}, y: {})\n", x, y);
			}

			if (x < width - 1)
			{
				ImGui::SameLine();
			}

			ImGui::PopID();
		}
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
