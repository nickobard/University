#include "GameLocator.hpp"

GameMap::GameMap(const string &path) {
    LoadMap(path);
    LoadRenderMap();
    GameStateNormal::SetBonusAmount(mapInfo_.bonuses_);
}

GameMap::~GameMap() {
    ClearMap();
}

void GameMap::LoadMap(const string &path) {

    TileNodeBuilder builder;

    try {
        MapReader reader(path);
        MapParser parser(reader.GetTilesData());
        builder.LoadTileNodes(parser.GetTilesInfo(), reader.GetMapHeader());
    } catch (...) {
        cerr << "Error: Map " + path + " could not be loaded!" << endl;
        builder.ClearTileNodes();
        throw exception();
    }

    tileNodesArray2D_ = builder.GetTileNodesMap();
    mapInfo_ = builder.GetMapInfo();
}

void GameMap::RenderMap() const {
    for (const auto *tile: renderTilesArray_) {
        tile->Render();
    }
}


Vector2<int> GameMap::CentralizePosition(const Vector2<int> &position) {
    auto deltaPosition = Vector2<int>(TILE_SIZE, TILE_SIZE) / 2 - position % TILE_SIZE;
    return position + deltaPosition;
}

Vector2<int> GameMap::GetPixelsPosition(const Vector2<int> &position) {
    return position * TILE_SIZE + TILE_SIZE / 2;
}

void GameMap::ClearMap() {
    for (auto &row: tileNodesArray2D_)
        for (auto col: row)
            delete col;

    renderTilesArray_.clear();
}

void GameMap::LoadRenderMap() {
    for (const auto &row: tileNodesArray2D_)
        for (auto col: row) {
            auto tile = col->GetTile();
            renderTilesArray_.push_back(tile);
        }
}

