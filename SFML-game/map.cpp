#include "Map.h"

Map::Map(int width, int height) : width(width), height(height) {
    // Optionally initialize the tiles vector with default tiles
    for (int i = 0; i < height; i++)
    {
        std::vector<Tile> row;
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                sf::Vector2f position(j * 20, i * 20);
                row.push_back(Tile(position, TextureType::Wall));
            }
            else
            {
                sf::Vector2f position(j * 20, i * 20);
                row.push_back(Tile(position, TextureType::Grass));
            }
        }
        tiles.push_back(row);
    }
}

void Map::loadMap(const std::vector<std::vector<TextureType>>& layout) {
    //tiles.clear(); // Clear current map
    //for (size_t i = 0; i < layout.size(); ++i) {
    //    std::vector<Tile> row;
    //    for (size_t j = 0; j < layout[i].size(); ++j) {
    //        // Assuming (j, i) is the position. Adjust as needed for your coordinate system.
    //        Tile tile({ j * 20, i * 20 }, layout[i][j]); // TILE_SIZE is a constant defining the size of a tile
    //        row.push_back(tile);
    //    }
    //    tiles.push_back(row);
    //}
}

void Map::draw(sf::RenderWindow* window) {
    /*for (auto row : tiles) {
        for (auto tile : row) {
            tile.draw(window);
        }
    }*/
    for (std::vector<Tile> v : tiles) {
        for (Tile tile : v) {
            tile.draw(window);
        }
    }
}

bool Map::collisionCheck(const sf::Vector2f& nextPosition) const {
    int x = static_cast<int>(nextPosition.x) / 20;
    int y = static_cast<int>(nextPosition.y) / 20;

    // Check boundaries
    //if (x < 1 || x >= width || y < 1 || y >= height) return true; // Collision with map boundaries is now redundant when walls are not passable

    return !tiles[y][x].isPassable();
}