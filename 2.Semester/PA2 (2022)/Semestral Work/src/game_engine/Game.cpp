#include "Game.hpp"

Game::~Game(){
  FreeGame();
}

void Game::FreeGame(){
  // free every gameObject in the game
  FreeGameObjects();
  // free locator
  FreeGameLocator();
} 

void Game::GameInit(){
  InitGameLocator();
  InitGameObjects();
}

void Game::InitGameObjects() {
  gameActors_.emplace_back(
                            new Pacman 
    (new TransformComponent({300,300},LEFT),
     new GraphicsComponent (GameLocator::GetFilesystem().GetTexture(GameFilesystem::PACMAN_TEXTURE)))
                          );

  gameControllers_.emplace_back(new Controller(new PlayerController(gameActors_[0])));
}

void Game::InitGameLocator() const {
  GameLocator::InitLocator();
  GameLocator::ProvideGraphics( new GameGraphics );
  GameLocator::ProvideFilesystem (new GameFilesystem );
  GameLocator::ProvideTime( new GameTime );
  GameLocator::ProvideMap( new GameMap );
}

void Game::GameStart(){
  GameInit();
  GameLoop();
}

void Game::GameLoop(){

  GameLocator::GetTime().InitGameTicks();
  while( ! events_.isQuit() )
  {
    GameLocator::GetTime().UpdateCurrentTicks();
    UpdateGame();
    RenderGame();
    GameLocator::GetTime().UpdateLastTicks();
  }
}

void Game::UpdateGameObjects(){
  for ( auto obj : gameControllers_){
    obj->Update();
  }
  for ( auto obj : gameActors_){
    obj->Update();
  }
}

void Game::RenderGameObjects(){
 for ( auto obj : gameActors_){
    obj->Render();
  }
}

void Game::FreeGameObjects(){
  for ( auto obj : gameActors_)
    delete obj;
  for ( auto obj : gameControllers_)
    delete obj;
}


void Game::UpdateGame() {
  events_.ProcessInput();
  UpdateGameObjects();

}

void Game::RenderGame() {
  GameLocator::GetGraphics().ClearRender();
  RenderGameObjects();
  GameLocator::GetGraphics().RenderGame();
}


void Game::FreeGameLocator(){
  GameLocator::QuitLocator();
}
