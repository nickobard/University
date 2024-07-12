#include "MapParser.hpp"
#include "../game_engine/GameLocator.hpp"

MapParser::MapParser(const vector<vector<TileData>> &tilesData, const MapHeader &header) {
    if (!ParseMap(tilesData, header)) {
        cerr << "Parse error: Could not parse map!" << endl;
        throw exception();
    }
}

bool MapParser::ParseMap(const vector<vector<TileData>> &tilesData, const MapHeader &header) {

    header_ = header;

    for (size_t row = 0, rows = tilesData.size(); row < rows; row++) {
        tilesInfo.emplace_back();
        for (size_t col = 0, cols = tilesData[row].size(); col < cols; col++) {
            try {
                auto tileInfo = ParseTile(tilesData[row][col], {col, row});
                tilesInfo[row].push_back(tileInfo);
            } catch (...) {
                return false;
            }
        }
    }
    return true;
}

TileInfo MapParser::ParseTile(TileData tileData, const Vector2<int> &tilePos) {

    TileInfo info;

    info.type_ = ParseTileType(tileData.type_);
    info.option_ = ParseOptionType(tileData.option_);
    info.direction_ = ParseTileDirection(tileData.direction_);
    info.position_ = ParseTilePosition(tilePos);

    return info;
}

TileType MapParser::ParseTileType(char tileType) {

    switch (tileType) {
        case '_':
            return TileType::EMPTY;
        case '#':
            return TileType::WALL;
        case 'x':
            return TileType::CROSS;
        case '=':
            return TileType::TUNNEL;
        case '@':
            return TileType::PORTAL;
        case '0':
            return TileType::NULL_TILE;
        default:
            cerr << "Parse error: Wrong tile type: '" << tileType << "'" << endl;
            throw exception();
    }
}

TileOption MapParser::ParseOptionType(char tileOption) {

    switch (tileOption) {
        case '.':
            return TileOption::BONUS;
        case 'o':
            return TileOption::BIG_BONUS;
        case '8':
            return TileOption::CHERRY;
        case '+':
            return TileOption::INNER_WALL_CORNER;
        case '*':
            return TileOption::OUTER_WALL_CORNER;
        default:
            return TileOption::NONE;

    }
}

Vector2<float> MapParser::ParseTileDirection(char tileDirection) {
    switch (tileDirection) {
        case 'v':
            return Vector2<float>::Down();
        case '^':
            return Vector2<float>::Up();
        case '>':
            return Vector2<float>::Right();
        case '<':
            return Vector2<float>::Left();
        default:
            return Vector2<float>::Zero();
    }

}

Vector2<float> MapParser::ParseTilePosition(const Vector2<int> &tilePosition) {
    auto position = GameMap::GetPixelsPosition(tilePosition);

    auto offsetLeft = (SCREEN_WIDTH - header_.mapSize_.second * TILE_SIZE) / 2;
    auto offsetUp = (SCREEN_HEIGHT - header_.mapSize_.first * TILE_SIZE) / 2;

    return position + Vector2<int>(offsetLeft, offsetUp);
}
