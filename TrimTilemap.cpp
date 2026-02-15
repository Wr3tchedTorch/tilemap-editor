#include "Tilemap.h"

void Tilemap::trimTilemap()
{
	int lastRowWithValues = -1;
	int lastColWithValues = -1;

	bool foundAnyValues = false;

	for (int i = 0; i < m_ArrayLevel.size(); ++i)
	{
		if (m_ArrayLevel[i].m_Id != 0)
		{
			foundAnyValues = true;

			int currentRow = i / m_LevelSize.x;
			int currentCol = i % m_LevelSize.x;

			lastRowWithValues = std::max(currentRow, lastRowWithValues);
			lastColWithValues = std::max(currentCol, lastColWithValues);
		}
	}

	if (!foundAnyValues)
	{
		m_ArrayLevel.clear();
		m_LevelSize = { 0, 0 };
		return;
	}

	std::vector<Tile> newArray;
	for (int row = 0; row <= lastRowWithValues; ++row)
	{
		for (int col = 0; col <= lastColWithValues; ++col)
		{
			newArray.push_back(m_ArrayLevel[col + static_cast<size_t>(row) * m_LevelSize.x]);
		}
	}

	m_ArrayLevel = newArray;
}