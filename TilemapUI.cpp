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

void TilemapUI::rightMouseButtonPressed()
{
	leftMouseButtonPressed();
}

void TilemapUI::updateSelectedGridSize()
{
	m_SelectedGridTiles.size = {
		m_GridMousePosition.x - m_SelectedGridTiles.position.x + 1,
		m_GridMousePosition.y - m_SelectedGridTiles.position.y + 1,
	};
}

void TilemapUI::leftMouseButtonReleased()
{
	updateSelectedGridSize();

	m_MapLayers[m_SelectedLayerIndex].placeTiles(m_SelectedGridTiles, Tile{ m_SelectedTileIndex });
}

void TilemapUI::rightMouseButtonReleased()
{
	updateSelectedGridSize();

	m_MapLayers[m_SelectedLayerIndex].removeTiles(m_SelectedGridTiles);
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
	ImGui::Text(std::format("Tile size: (width: {}, height: {})", m_TileSize.x, m_TileSize.y).c_str());
	ImGui::Text(std::format("grid mouse position: (x: {}, y: {})", m_GridMousePosition.x, m_GridMousePosition.y).c_str());	
	ImGui::Text(std::format("Selected layer: `{}`", m_MapLayers[m_SelectedLayerIndex].getLevelFilepath()).c_str());

	drawTilemapUI();
}

