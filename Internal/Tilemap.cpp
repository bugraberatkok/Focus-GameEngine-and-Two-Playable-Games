#include "TileMap.h"
#include <SDL_image.h>
#include <fstream>
#include <sstream>

bool TileMap::LoadCSV(const std::string& path, std::vector<int>& out)
{
    std::ifstream file(path);
    if (!file.is_open()) return false;

    out.clear();
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ','))
            out.push_back(std::stoi(cell));
    }
    return true;
}

bool TileMap::LoadFromCSV(
    SDL_Renderer* renderer,
    const std::string& tilesetPath,
    int tileSize_,
    int mapWidth,
    int mapHeight,
    const std::string& groundCSV)
{
    tileSize = tileSize_;
    mapW = mapWidth;
    mapH = mapHeight;

    if (!LoadCSV(groundCSV, ground)) return false;

    tileset = IMG_LoadTexture(renderer, tilesetPath.c_str());
    if (!tileset) return false;

    int texW, texH;
    SDL_QueryTexture(tileset, nullptr, nullptr, &texW, &texH);
    tilesetCols = texW / tileSize;

    return true;
}

void TileMap::Render(SDL_Renderer* renderer)
{
    if (!tileset || mapW <= 0 || mapH <= 0 || tileSize <= 0)
        return;

    SDL_Rect src{ 0, 0, tileSize, tileSize };
    SDL_Rect dst{ 0, 0, tileSize, tileSize };


   
    for (int y = 0; y < mapH; ++y)
    {
        for (int x = 0; x < mapW; ++x)
        {
            const int i = y * mapW + x;
            if (i < 0 || i >= (int)ground.size())
                continue;

            const int tileIndex = ground[i];

            
            if (tileIndex < 0)
                continue;

            src.x = (tileIndex % tilesetCols) * tileSize;
            src.y = (tileIndex / tilesetCols) * tileSize;

            
            dst.x = x * tileSize;
            dst.y = y * tileSize;

            SDL_RenderCopy(renderer, tileset, &src, &dst);
        }
    }
}

int TileMap::GetTileAt(int tileX, int tileY) const
{
    if (tileX < 0 || tileY < 0 || tileX >= mapW || tileY >= mapH)
        return -1;

    int index = tileY * mapW + tileX;
    if (index >= (int)ground.size())
        return -1;

    return ground[index];
}

