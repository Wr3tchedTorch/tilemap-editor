#include "TilemapUI.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/Sprite.hpp>

void TilemapUI::drawTilemapUI()
{
	sf::Sprite iconsSprite(*m_TextureTilemap);

	float tileSizeFloat = static_cast<float>(m_TileSize);

	int width = m_TilemapSize.x;
	int height = m_TilemapSize.y;

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			ImGui::PushID(y * width + x);

			int left = x * m_TileSize;
			int top = y * m_TileSize;

			iconsSprite.setTextureRect({ {left, top}, {m_TileSize, m_TileSize} });

			bool pressed = ImGui::ImageButton("##tile", iconsSprite, {32, 32});

			if (pressed)
			{
				m_SelectedTile = { x, y };
			}

			if (m_SelectedTile.x == x && m_SelectedTile.y == y)
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