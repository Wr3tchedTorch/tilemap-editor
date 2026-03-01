#include <format>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "TilemapUI.h"
#include "imgui.h"
#include "Tile.h"
#include "Tilemap.h"
#include "TextureHolder.h"
#include "imgui_stdlib.h"
#include <cstdio>

TilemapUI::TilemapUI(sf::RenderWindow& window) : m_Window(window)
{
}

void TilemapUI::leftMouseButtonPressed()
{
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
	{
		m_IsMouseDragValid = false;
		return;
	}

	m_SelectedGridTiles = {
		{
			m_GridMousePosition.x,
			m_GridMousePosition.y,
		},
		{ 1, 1 }
	};

	m_IsMouseDragValid = true;
}

void TilemapUI::rightMouseButtonPressed()
{
	leftMouseButtonPressed();
}

void TilemapUI::updateSelectedGridSize()
{
	if (m_SelectedGridTiles.position.x > m_GridMousePosition.x)
	{
		m_SelectedGridTiles.size.x     = m_SelectedGridTiles.position.x - m_GridMousePosition.x + 1;
		m_SelectedGridTiles.position.x = m_GridMousePosition.x;
	}
	else
	{
		m_SelectedGridTiles.size.x = m_GridMousePosition.x - m_SelectedGridTiles.position.x + 1;
	}

	if (m_SelectedGridTiles.position.y > m_GridMousePosition.y)
	{
		m_SelectedGridTiles.size.y	   = m_SelectedGridTiles.position.y - m_GridMousePosition.y + 1;
		m_SelectedGridTiles.position.y = m_GridMousePosition.y;
	}
	else
	{
		m_SelectedGridTiles.size.y = m_GridMousePosition.y - m_SelectedGridTiles.position.y + 1;
	}
}

void TilemapUI::leftMouseButtonReleased()
{
	if (!m_IsMouseDragValid || m_SelectedLayerIndex >= m_MapLayers.size())
	{
		return;
	}

	updateSelectedGridSize();

	m_MapLayers[m_SelectedLayerIndex]->placeTiles(m_SelectedGridTiles, Tile{ m_SelectedTileIndex });
}

void TilemapUI::rightMouseButtonReleased()
{
	if (!m_IsMouseDragValid || m_SelectedLayerIndex >= m_MapLayers.size())
	{
		return;
	}

	updateSelectedGridSize();

	m_MapLayers[m_SelectedLayerIndex]->removeTiles(m_SelectedGridTiles);
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

	m_MapLayers.push_back(std::make_unique<Tilemap>(newTilemap));
}

void TilemapUI::removeLayer(int index)
{
	m_MapLayers.erase(m_MapLayers.begin() + index);
}

void TilemapUI::switchLayers(int index, int other)
{
	std::swap(m_MapLayers[index], m_MapLayers[other]);
}

void TilemapUI::saveCurrentLevel()
{
	for (auto& layer : m_MapLayers)
	{
		layer->saveLevelToDisk();
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
	m_GridMousePosition.x = mapWorldPosition.x / static_cast<int>(m_TileSize.x);
	m_GridMousePosition.y = mapWorldPosition.y / static_cast<int>(m_TileSize.y);
}

void TilemapUI::render()
{
	ImGui::Text(std::format("texture file: {}", m_FilepathTilemap).c_str());
	ImGui::Text(std::format("Tilemap size: (width: {}, height: {})", m_TilemapSize.x, m_TilemapSize.y).c_str());
	ImGui::Text(std::format("Tile size: (width: {}, height: {})", m_TileSize.x, m_TileSize.y).c_str());
	ImGui::Text(std::format("grid mouse position: (x: {}, y: {})", m_GridMousePosition.x, m_GridMousePosition.y).c_str());	
	ImGui::Text(std::format("Selected layer: `{}`", m_MapLayers[m_SelectedLayerIndex]->getLevelFilepath()).c_str());
	ImGui::Button("Save Tilemap");

	static std::string myText = "";

	if (ImGui::InputText("Enter Name", &myText))
	{
		printf("Current content: %s\n", myText.c_str());
	}

	drawTilemapUI();
}

void TilemapUI::drawTilemap()
{
	for (auto& layer : m_MapLayers)
	{
		m_Window.draw(*layer);
	}
}

