#ifndef _MAPLOADER_H_
#define _MAPLOADER_H_

#include "./GameVars.h"

class MapLoader {

public:
	static void loadMap();
};

void MapLoader::loadMap() {

	tileSet = (Bitmap)al_load_bitmap(TILESET_PATH);

	if (!tileSet) {
		std::cout << "Could not load the TileSet!" << std::endl;
		exit(-1);
	}

	gameMap = new TileLayer(TILEMAP_HEIGHT, TILEMAP_WIDTH, tileSet, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	//clipper = MakeTileLayerClipper(gameMap);

	if (!gameMap->ReadText(SKY_PATH)) {
		std::cout << "Failed to read Sky Map";
		exit(-1);
	}

	if (!gameMap->ReadText(BACKGROUND_PATH)) {
		std::cout << "Failed to read Background Map";
		exit(-1);
	}

	if (!gameMap->ReadText(FLAG_PATH)) {
		std::cout << "Failed to read Flag Map";
		exit(-1);
	}

	if (!gameMap->ReadText(TERRAIN_PATH)) {
		std::cout << "Failed to read Terrain Map";
		exit(-1);
	}

	GridComputation::ComputeTileGridBlocks1(gameMap);
}

#endif _MAPLOADER_H_
