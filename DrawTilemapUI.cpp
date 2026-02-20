#include "TilemapUI.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/Sprite.hpp>

void TilemapUI::drawTilemapUI()
{
	sf::Sprite iconsSprite(*m_TextureTilemap);

	float tileSizeFloatX = static_cast<float>(m_TileSize.x);
	float tileSizeFloatY = static_cast<float>(m_TileSize.y);

	int width  = m_TilemapSize.x;
	int height = m_TilemapSize.y;

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			ImGui::PushID(y * width + x);

			int left = x * m_TileSize.x;
			int top  = y * m_TileSize.y;

			iconsSprite.setTextureRect({ {left, top}, {static_cast<int>(m_TileSize.x), static_cast<int>(m_TileSize.y)} });

			bool pressed = ImGui::ImageButton("##tile", iconsSprite, { 32, 32 });

			if (pressed)
			{
				m_SelectedTileIndex = x + y * m_TilemapSize.x;
			}

			int selectedTileX = m_SelectedTileIndex % m_TilemapSize.x;
			int selectedTileY = m_SelectedTileIndex / m_TilemapSize.x;

			if (selectedTileX == x && selectedTileY == y)
			{
				ImDrawList* drawList = ImGui::GetWindowDrawList();
				ImVec2 posMin = ImGui::GetItemRectMin();
				ImVec2 posMax = ImGui::GetItemRectMax();

				drawList->AddRect(posMin, posMax, IM_COL32(255, 255, 255, 255), 0.0f, 0, 2.0f);
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
