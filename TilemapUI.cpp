#include <format>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include "TilemapUI.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Tile.h"
#include "Tilemap.h"
#include "TextureHolder.h"

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
	if (m_MapLayers.size() >= m_SelectedLayerIndex)
	{
		return;
	}

	updateSelectedGridSize();

	m_MapLayers[m_SelectedLayerIndex].placeTiles(m_SelectedGridTiles, Tile{ m_SelectedTileIndex });
}

void TilemapUI::rightMouseButtonReleased()
{
	if (m_MapLayers.size() >= m_SelectedLayerIndex)
	{
		return;
	}

	updateSelectedGridSize();

	m_MapLayers[m_SelectedLayerIndex].removeTiles(m_SelectedGridTiles);
}

void TilemapUI::loadTilemap(std::string filepathTilemap, sf::Vector2u tileSize, sf::Vector2u tilemapSize)
{
	m_FilepathTilemap = filepathTilemap;
	m_TextureTilemap  = &TextureHolder::GetTexture(filepathTilemap);
	
	m_TilemapSize = tilemapSize;
	m_TileSize    = tileSize;

	m_MapLayers.clear();
}

void TilemapUI::addLayer(std::string filepathLayer)
{
	Tilemap newTilemap(
		*m_TextureTilemap,
		filepathLayer,
		m_TileSize,
		m_TilemapSize
	);

	m_MapLayers.push_back(newTilemap);
}

void TilemapUI::removeLayer(int index)
{
	m_MapLayers.erase(m_MapLayers.begin() + index);
}

void TilemapUI::switchLayers(int index, int other)
{
	std::string firstFilepathLevel = m_MapLayers[index].getLevelFilepath();

	m_MapLayers[index].loadLevelFromDisk(m_MapLayers[other].getLevelFilepath());
	m_MapLayers[other].loadLevelFromDisk(firstFilepathLevel);
}

void TilemapUI::saveCurrentLevel()
{
	for (Tilemap& layer : m_MapLayers)
	{
		layer.saveLevelToDisk();
	}
}

void TilemapUI::closeCurrentLevel()
{
	saveCurrentLevel();

	m_FilepathCurrentLevel = "";
	m_SelectedLayerIndex   = 0;

	m_MapLayers.clear();
}

void TilemapUI::update(sf::Vector2f mapWorldPosition)
{	
	m_GridMousePosition.x = static_cast<int>(mapWorldPosition.x) / m_TileSize.x;
	m_GridMousePosition.y = static_cast<int>(mapWorldPosition.y) / m_TileSize.y;
}

void TilemapUI::render()
{
	ImGui::Text(std::format("texture file: {}", m_FilepathTilemap).c_str());
	ImGui::Text(std::format("Tilemap size: (width: {}, height: {})", m_TilemapSize.x, m_TilemapSize.y).c_str());
	ImGui::Text(std::format("Tile size: (width: {}, height: {})", m_TileSize.x, m_TileSize.y).c_str());
	ImGui::Text(std::format("grid mouse position: (x: {}, y: {})", m_GridMousePosition.x, m_GridMousePosition.y).c_str());	
	ImGui::Text(std::format("Selected layer: `{}`", m_MapLayers[m_SelectedLayerIndex].getLevelFilepath()).c_str());

	if (m_FilepathTilemap.empty())
	{
		ImGui::Text(std::format("No tilemap selected!").c_str());
		return;
	}

	drawTilemapUI();
}

