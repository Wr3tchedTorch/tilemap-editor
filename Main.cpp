#include "Engine.h"
#include "Tilemap.h"
#include <iostream>

int main()
{		
	TextureHolder hold;

	const sf::Texture& textureTilemap = TextureHolder::GetTexture("./graphics/tilemap.png");

	Tilemap map(textureTilemap, "./levels/test.dat");

	map.removeTile({ 0, 5 });
	map.removeTile({ 6, 6 });

	map.saveLevelToDisk();

	std::cout << map.levelToString();


	//Engine engine;

	// engine.run();

	return 0;
}
