#include "TilemapUI.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "TextureHolder.h"
#include <format>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include "Tile.h"

TilemapUI::TilemapUI(const sf::Window& window) : m_Window(window)
{
}

void TilemapUI::leftMouseButtonPressed()
{
	m_SelectedGridTiles = {
		{
			m_GridMousePosition.x,
			m_GridMousePosition.y,
		},
		{ 1, 1 }
	};
}

void TilemapUI::leftMouseButtonReleased()
{
	m_SelectedGridTiles.size = {
		m_GridMousePosition.x - m_SelectedGridTiles.position.x,
		m_GridMousePosition.y - m_SelectedGridTiles.position.y,
	};

	m_MapLayers[selectedLayerIndex].placeTiles(m_SelectedGridTiles, Tile{ m_SelectedTileIndex });
}

void TilemapUI::update(sf::Vector2f mapWorldPosition)
{	
	m_GridMousePosition.x = mapWorldPosition.x / m_TileSize.x;
	m_GridMousePosition.y = mapWorldPosition.y / m_TileSize.y;
}

void TilemapUI::render()
{
	ImGui::Text(std::format("texture file: {}", m_FilepathTilemap).c_str());
	ImGui::Text(std::format("Tilemap size: (width: {}, height: {})", m_TilemapSize.x, m_TilemapSize.y).c_str());

	ImGui::Text(std::format("grid mouse position: (x: {}, y: {})", m_GridMousePosition.x, m_GridMousePosition.y).c_str());	

	drawTilemapUI();
}

