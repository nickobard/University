#include "MapReader.hpp"

MapReader::MapReader(const string &path) {
    if (!Read(path)) {
        cerr << "Read error: Could not read map!" << endl;
        throw exception();
    }
}

bool MapReader::Read(const string &path) {
    return OpenMapFile(path) && ReadMapHeader() && ReadMaps();
}

MapReader::~MapReader() {
    mapFileInput_.close();
}


bool MapReader::OpenMapFile(const string &path) {

    mapFileInput_.open(path);

    if (mapFileInput_.fail()) {
        cerr << "Read error: Could not open map file!" << endl;
        return false;
    }

    return true;
}

bool MapReader::ReadMapHeader() {

    if (!ReadSize()) {
        cerr << "Read header error: Could not read map size." << endl;
        return false;
    }

    if (!ReadSpawns()) {
        cerr << "Read header error: Could not read spawns." << endl;
        return false;
    }

    if (!ReadPortals()) {
        cerr << "Read header error: Could not read portals." << endl;
        return false;
    }
    return true;
}

bool MapReader::ReadSize() {
    if (!CheckDataType("size:"))
        return false;

    auto &[rows, columns] = header_.mapSize_;
    if (!(mapFileInput_ >> rows >> columns)) {
        return false;
    }
    return true;
}


bool MapReader::ReadSpawns() {

    if (!CheckDataType("spawns:") || !OpenBrace())
        return false;

    auto &[pacmanSpawn, ghostSpawn] = header_.spawnPoints_;

    if (!CheckDataType("pacman:") || !ReadPosition(pacmanSpawn))
        return false;

    if (!CheckDataType("ghost:") || !ReadPosition(ghostSpawn))
        return false;

    return CloseBrace();
}

bool MapReader::ReadPosition(Vector2<int> &position) {
    if (!(mapFileInput_ >> position.y_ >> position.x_))
        return false;
    position = position - 1;
    return true;
}

bool MapReader::ReadPortals() {

    if (!CheckDataType("portals:")) {
        header_.noPortals_ = true;
        return true;
    } else
        header_.noPortals_ = false;

    auto &[first, second] = header_.portalsPair_;
    if (!OpenBrace() || !ReadPosition(first) || !ReadPosition(second) || !CloseBrace())
        return false;
    return true;
}

bool MapReader::ReadMaps() {

    if (!InitMap()) {
        cerr << "Read error: Could not initialize map." << endl;
        return false;
    }
    if (!ReadMap("typemap:") || !ReadMap("options:") || !ReadMap("directions:")) {
        cerr << "Read error: Could not read maps!" << endl;
        return false;
    }

    return true;
}

bool MapReader::OpenBrace() {
    if (char brace; !(mapFileInput_ >> brace) || brace != '{') {
        cerr << "Read error: Expected open brace '{'. Get: " << brace << endl;
        return false;
    }
    return true;
}

bool MapReader::CloseBrace() {
    if (char brace; !(mapFileInput_ >> brace) || brace != '}') {
        cerr << "Read error: Expected close brace '}'. Get: " << brace << endl;
        return false;
    }
    return true;
}

bool MapReader::CheckDataType(const string &dataType) {

    streampos lastReadPosition = mapFileInput_.tellg();

    if (string data; !(mapFileInput_ >> data)) {
        cerr << "Read error: Failed to read file!" << endl;
        return false;
    } else if (data != dataType) {
        cerr << "Read error: Expected: " + dataType + " Get: " + data << endl;
        mapFileInput_.seekg(lastReadPosition);
        return false;
    }
    return true;
}

bool MapReader::InitMap() {

    auto [rows, columns] = header_.mapSize_;
    if (rows == 0 && columns == 0) {
        cerr << "Read error: Map has 0 rows and 0 columns." << endl;
        return false;
    }

    tilesData = vector<vector<TileData>>(rows);

    for (auto &row: tilesData)
        row = vector<TileData>(columns);

    return true;
}


bool MapReader::ReadMap(const string &type) {
    if (!CheckDataType(type) || !OpenBrace())
        return false;

    if (type == "typemap:" && !ReadTiles()) {
        cerr << "Read error: Could not read tiles types." << endl;
        return false;
    } else if (type == "options:" && !ReadOptions()) {
        cerr << "Read error: Could not read tiles options." << endl;
        return false;
    } else if (type == "directions:" && !ReadDirections()) {
        cerr << "Read error: Could not read tiles directions." << endl;
        return false;
    }

    if (!CloseBrace())
        return false;

    return true;
}

bool MapReader::ReadTiles() {
    for (auto &row: tilesData) {
        for (auto &tileData: row) {
            if (!(mapFileInput_ >> tileData.type_)) {
                cerr << "Read error: Could read tile type." << endl;
                return false;
            }
        }
    }
    return true;
}

bool MapReader::ReadOptions() {
    for (auto &row: tilesData) {
        for (auto &tileData: row) {
            if (!(mapFileInput_ >> tileData.option_)) {
                cerr << "Read error: Could read tile option." << endl;
                return false;
            }
        }
    }
    return true;
}

bool MapReader::ReadDirections() {
    for (auto &row: tilesData) {
        for (auto &tileData: row) {
            if (!(mapFileInput_ >> tileData.direction_)) {
                cerr << "Read error: Could read tile direction." << endl;
                return false;
            }
        }
    }
    return true;
}



