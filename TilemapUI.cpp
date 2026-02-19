#include "TilemapUI.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "TextureHolder.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

TilemapUI::TilemapUI(const sf::Window& window, std::string filepathTilemap, std::string filepathLevel) :
	m_Window(window),
	m_TextureTilemap(&TextureHolder::GetTexture(filepathTilemap))
{
}

void TilemapUI::leftMouseButtonPressed()
{
	//m_Tilemap.placeTile(m_GridMousePosition);
}

void TilemapUI::rightMouseButtonPressed()
{
	//m_Tilemap.removeTile(m_GridMousePosition);
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

	drawTilemapUI();
}

