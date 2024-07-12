#include "Game.hpp"
#include "GameLocator.hpp"


Game::~Game() {
    FreeGameObjects();
    GameLocator::QuitLocator();
}

void Game::GameInit() {
    InitGameLocator();
    InitGameObjects();
}

void Game::InitGameObjects() {
    gameActors_.emplace_back(
            new Pacman(
                    new TransformComponent(GameLocator::GetMap().GetMapInfo().playerSpawn_->GetTransform()->position_,
                                           Vector2<float>::Right()),
                    new GraphicsComponent(GameLocator::GetFilesystem().GetTexture(TextureType::PACMAN)))
    );

    gameActors_.emplace_back(
            new Ghost(new TransformComponent(GameLocator::GetMap().GetMapInfo().ghostsSpawn_->GetTransform()->position_,
                                             Vector2<float>::Right()),
                      new GraphicsComponent(GameLocator::GetFilesystem().GetTexture(TextureType::GHOST)))
    );

    gameControllers_.emplace_back(new Controller(new PlayerController(gameActors_[0])));
    gameControllers_.emplace_back(new Controller(new AIComponent(gameActors_[1], gameActors_[0])));
}

void Game::InitGameLocator() {
    GameLocator::InitLocator();
    GameLocator::ProvideGraphics(new GameGraphics);
    GameLocator::ProvideFilesystem(new GameFilesystem);
    GameLocator::ProvideMap(new GameMap("assets/maps/map5.map"));
    GameLocator::ProvideTime(new GameTime);
    GameLocator::ProvideManager(new GameManager(*this));
}

void Game::GameStart() {
    try {
        GameInit();
    }
    catch (...) {
        cerr << "Error: Could not initialize game! Aborting..." << endl;
        return;
    }
    GameLoop();
}

void Game::GameLoop() {

    GameLocator::GetTime().InitGameTicks();
    while (!events_.isQuit()) {
        GameLocator::GetTime().UpdateCurrentTicks();
        UpdateGame();
        RenderGame();
        GameLocator::GetTime().UpdateLastTicks();
    }
}

void Game::UpdateGameObjects() {
    for (auto obj: gameControllers_) {
        obj->Update();
    }
    for (auto obj: gameActors_) {
        obj->Update();
    }
}

void Game::RenderGameObjects() {
    for (auto obj: gameActors_) {
        obj->Render();
    }
}

void Game::FreeGameObjects() {
    for (auto obj: gameActors_)
        delete obj;
    for (auto obj: gameControllers_)
        delete obj;
}


void Game::UpdateGame() {
    events_.ProcessInput();
    GameLocator::GetManager().Update();
    UpdateGameObjects();

}

void Game::RenderGame() {
    GameLocator::GetGraphics().ClearRender();
    GameLocator::GetMap().RenderMap();
    RenderGameObjects();
    GameLocator::GetGraphics().RenderGame();
}

void Game::QuitGame() {
    events_.QuitGame();
}
