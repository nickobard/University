#include "TileNodeBuilder.hpp"
#include "../game_engine/GameLocator.hpp"

TileNodeBuilder::TileNodeBuilder()
        : filesystem_(GameLocator::GetFilesystem()) {}

void TileNodeBuilder::BuildTileNodes(const vector<vector<TileInfo>> &tilesInfo) {

    size_t currentRow = 0;

    for (auto &row: tilesInfo) {
        tileNodes_.emplace_back();
        for (auto &info: row) {
            auto tileNode = BuildTileNode(info);
            tileNodes_[currentRow].push_back(tileNode);
        }
        currentRow++;
    }
}

TileNode *TileNodeBuilder::BuildTileNode(const TileInfo &tileInfo) {

    if (tileInfo.type_ == TileType::EMPTY)
        return BuildEmptyTileNode(tileInfo);
    else if (tileInfo.type_ == TileType::WALL)
        return BuildWallTileNode(tileInfo);
    else if (tileInfo.type_ == TileType::CROSS)
        return BuildCrossTileNode(tileInfo);
    else if (tileInfo.type_ == TileType::TUNNEL)
        return BuildTunnelTileNode(tileInfo);
    else if (tileInfo.type_ == TileType::PORTAL)
        return BuildPortalTileNode(tileInfo);
    else if (tileInfo.type_ == TileType::NONE)
        return BuildNullTileNode(tileInfo);
    else {
        cerr << "Build tile error: Unrecognized tile type." << endl;
        throw exception();
    }

}

TileNode *TileNodeBuilder::BuildEmptyTileNode(const TileInfo &tileInfo) {
    auto tileNode = new TileNode(new EmptyTile(filesystem_.GetTexture(TextureType::EMPTY), tileInfo.position_));
    AddOption(tileNode, tileInfo.option_);
    return tileNode;
}

TileNode *TileNodeBuilder::BuildCrossTileNode(const TileInfo &tileInfo) {
    auto tileNode = new TileNode(new CrossTile(filesystem_.GetTexture(TextureType::CROSS), tileInfo.position_));
    AddOption(tileNode, tileInfo.option_);
    return tileNode;
}

TileNode *TileNodeBuilder::BuildWallTileNode(const TileInfo &tileInfo) {

    TileNode *tileNode;
    auto option = tileInfo.option_;

    if (option == TileOption::OUTER_WALL_CORNER)
        tileNode = new TileNode(new WallTile(filesystem_.GetTexture(TextureType::WALL), tileInfo.position_));
    else if (option == TileOption::INNER_WALL_CORNER)
        tileNode = new TileNode(new WallTile(filesystem_.GetTexture(TextureType::WALL), tileInfo.position_));
    else
        tileNode = new TileNode(new WallTile(filesystem_.GetTexture(TextureType::WALL), tileInfo.position_));
    return tileNode;
}

TileNode *TileNodeBuilder::BuildTunnelTileNode(const TileInfo &tileInfo) {
    auto tileNode = new TileNode(new TunnelTile(filesystem_.GetTexture(TextureType::TUNNEL), tileInfo.position_));
    AddOption(tileNode, tileInfo.option_);
    return tileNode;
}

TileNode *TileNodeBuilder::BuildNullTileNode(const TileInfo &tileInfo) {
    auto tileNode = new TileNode(new NullTile(tileInfo.position_));
    return tileNode;
}

TileNode *TileNodeBuilder::BuildPortalTileNode(const TileInfo &tileInfo) {
    if (header_.noPortals_) {
        cerr << "Build tile nodes error: Building portal tile node with no portals in game." << endl;
        throw exception();
    }
    auto tileNode = new TileNode(
            new PortalTile(filesystem_.GetTexture(TextureType::EMPTY), tileInfo.position_, tileInfo.direction_));
    AddOption(tileNode, tileInfo.option_);
    return tileNode;
}

void TileNodeBuilder::AddOption(TileNode *tileNode, TileOption option) {
    switch (option) {
        case TileOption::BONUS: {
            auto bonus = new Bonus(new GraphicsComponent(filesystem_.GetTexture(TextureType::BONUS)));
            if (tileNode->AddBonus(bonus))
                mapInfo_.bonuses_++;
            else
                delete bonus;
        }
            return;
        case TileOption::BIG_BONUS:
            return;
        case TileOption::CHERRY:
            return;
        default:
            return;
    }
}

void TileNodeBuilder::AddSpawns() {
    if (!CheckSpawnPoints()) {
        cerr << "Add spawn points error: Spawn points could not be set!" << endl;
        throw exception();
    }

    const auto &[player, ghosts] = header_.spawnPoints_;
    mapInfo_.playerSpawn_ = tileNodes_[player.y_][player.x_];
    mapInfo_.ghostsSpawn_ = tileNodes_[ghosts.y_][ghosts.x_];
}

void TileNodeBuilder::ConnectNodes() {

    for (size_t row = 0, rows = tileNodes_.size(); row < rows; row++)
        for (size_t col = 0, cols = tileNodes_[row].size(); col < cols; col++) {
            if (row >= 1)
                tileNodes_[row][col]->upperNode = tileNodes_[row - 1][col];
            if (row < rows - 1)
                tileNodes_[row][col]->bottomNode = tileNodes_[row + 1][col];
            if (col >= 1)
                tileNodes_[row][col]->leftNode = tileNodes_[row][col - 1];
            if (col < cols - 1)
                tileNodes_[row][col]->rightNode = tileNodes_[row][col + 1];
        }
}

void TileNodeBuilder::ClearTileNodes() {
    for (auto &row: tileNodes_)
        for (auto tile: row)
            delete tile;
}

void TileNodeBuilder::LoadTileNodes(const vector<vector<TileInfo>> &tilesInfo, const MapHeader &header) {
    header_ = header;
    BuildTileNodes(tilesInfo);
    AddSpawns();
    ConnectNodes();
    ConnectPortals();
}

void TileNodeBuilder::ConnectPortals() {
    if (header_.noPortals_)
        return;
    else if (!CheckPortals()) {
        cerr << "Connecting portals error: Portals could not be set!" << endl;
        throw exception();
    }

    const auto &[first, second] = header_.portalsPair_;
    const auto [firstPortal, secondPortal] = tie(tileNodes_[first.y_][first.x_], tileNodes_[second.y_][second.x_]);

    ConnectPortal(firstPortal, secondPortal);
    ConnectPortal(secondPortal, firstPortal);
}

void TileNodeBuilder::ConnectPortal(TileNode *entrance, TileNode *exit) {
    const auto &direction = entrance->GetTransform()->direction_;
    if (direction == Vector2<float>::Right())
        entrance->leftNode = exit;
    else if (direction == Vector2<float>::Left())
        entrance->rightNode = exit;
    else if (direction == Vector2<float>::Up())
        entrance->bottomNode = exit;
    else if (direction == Vector2<float>::Down())
        entrance->upperNode = exit;
    else {
        cerr << "Connecting portals error: wrong direction." << endl;
        throw exception();
    }
}

bool TileNodeBuilder::CheckSpawnPoints() {
    const auto &[playerSpawn, ghostSpawn] = header_.spawnPoints_;

    if (tileNodes_[playerSpawn.y_][playerSpawn.x_]->isObstacle()) {
        cerr << "Build tile nodes error: Player spawn point is on obstacle." << endl;
        return false;
    }
    if (tileNodes_[ghostSpawn.y_][ghostSpawn.x_]->isObstacle()) {
        cerr << "Build tile nodes error: Ghosts spawn point is on obstacle." << endl;
        return false;
    }
    return true;
}

bool TileNodeBuilder::CheckPortals() {
    if (header_.noPortals_)
        return true;

    const auto &[first, second] = header_.portalsPair_;
    const auto [firstNode, secondNode] = tie(tileNodes_[first.y_][first.x_], tileNodes_[second.y_][second.x_]);

    if (!firstNode->isPortal() || !secondNode->isPortal()) {
        cerr << "Build tile nodes error: Wrong portals positions - not on tiles with portal type." << endl;
        return false;
    }
    if (firstNode->GetTransform()->direction_ == Vector2<float>::Zero() ||
        firstNode->GetTransform()->direction_ == Vector2<float>::Zero()) {
        cerr << "Build tile nodes error: Portals don't have exit directions." << endl;
        return false;
    }
    return true;
}

