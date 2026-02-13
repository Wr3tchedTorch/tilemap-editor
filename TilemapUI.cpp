#include "TilemapUI.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "TextureHolder.h"

TilemapUI::TilemapUI() : Tilemap(*m_TextureTilemap, "bkdsaksdk")
{

}

void TilemapUI::loadTilemapTexture(std::string filepathTilemap)
{
	m_TextureTilemap = &TextureHolder::GetTexture(filepathTilemap);
	m_FilepathTilemap = filepathTilemap;
}

void TilemapUI::render()
{
	ImGui::Text(m_FilepathTilemap.c_str());
}
