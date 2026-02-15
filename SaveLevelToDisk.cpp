#include "Tilemap.h"
#include <iostream>
#include <fstream>

void Tilemap::saveLevelToDisk()
{
	std::ofstream outputFile(m_FilepathLevel);

	if (!outputFile.is_open())
	{
		std::cout << std::format("error while creating file at location `{}`!", m_FilepathLevel);
		return;
	}

	trimTilemap();

	std::string levelString = levelToString();
	outputFile.write(levelString.c_str(), levelToString().size());

	outputFile.close();
}