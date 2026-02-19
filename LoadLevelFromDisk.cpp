#include "Tilemap.h"
#include <iostream>
#include <fstream>

void Tilemap::loadLevelFromDisk(std::string filepathLevel)
{
	m_FilepathLevel = filepathLevel;

	std::ifstream inputFile(m_FilepathLevel);
	if (!inputFile.is_open())
	{
		std::cout << std::format("file `{}` not found!", m_FilepathLevel);
		return;
	}

	int width = 0, height = 0;

	std::string line;
	while (std::getline(inputFile, line))
	{
		width = 0;
		std::string cell;
		std::stringstream stream(line);
		while (std::getline(stream, cell, ','))
		{			
			if (cell.empty())
			{
				continue;
			}

			int tileId = std::stoi(cell);
			m_ArrayLevel.push_back(Tile{ tileId });

			width++;
		}
		height++;
	}

	m_LevelSize = {
		static_cast<unsigned int>(width),
		static_cast<unsigned int>(height)
	};

	inputFile.close();
}