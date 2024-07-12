#pragma once
#include "GameTime.hpp"
#include "GameMap.hpp"
#include "GameFilesystem.hpp"
#include "GameAudio.hpp"
#include "GameManager.hpp"
#include "GameGraphics.hpp"

/**
 * @brief Locator class which provides global access to global game services.
 * 
 * @details Provides global access to instances to game services - classes
 * that are used widely by the game and have only one instance.
 * 
 */
class GameLocator {

  public:

    /**
     * @brief Initializes locators members with nullptr.
     * 
     */
    static void InitLocator ();

    /**
     * @brief Deletes allocated services objects avoiding possibly lost memory
     * 
     */
    static void QuitLocator ();

    /**
     * @brief Initializes a Game Time service with provided object to locator.
     * 
     * @param time GameTime object for tracking time in the game.
     */
    static inline void ProvideTime       (GameTime * time)             ;

    /**
     * @brief Initializes a Game Map service with provided object to locator.
     * 
     * @param map GameMap object to represent game map from tiles in the game.
     */
    static inline void ProvideMap        (GameMap * map)               ;

    /**
     * @brief Initializes a Game Filesystem service with provided object to locator.
     * 
     * @param filesystem filesystem of the game - stores all textures and tiles.
     */
    static inline void ProvideFilesystem (GameFilesystem * filesystem) ;

    /**
     * @brief Initializes a Game Audio service with provided object to locator.
     * 
     * @param audio GameAudio object to play audio in the game.
     */
    static inline void ProvideAudio      (GameAudio * audio)           ;
    
    /**
     * @brief Initializes a Game Manager service with provided object to locator.
     * 
     * @param manager GameManager object to manage game state, score and modes.
     */
    static inline void ProvideManager    (GameManager * manager)       ;

    /**
     * @brief Initializes a Game Graphics service with provided object to locator.
     * 
     * @param graphics graphics of the game - window and renderer.
     */
    static inline void ProvideGraphics   (GameGraphics * graphics)     ;


    /**
     * @brief Get reference to the service.
     * 
     * @return GameTime& reference to the GameTime object.
     */
    static inline GameTime       & GetTime       ();
    /**
     * @brief Get reference to the service.
     * 
     * @return GameMap& reference to the GameMap object.
     */
    static inline GameMap        & GetMap        ();    
    /**
     * @brief Get reference to the service.
     * 
     * @return GameFilesystem& reference to the GameFilesystem object.
     */
    static inline GameFilesystem & GetFilesystem ();    
    // Get reference to the service.
    static inline GameAudio      & GetAudio      ();    
    // Get reference to the service.
    static inline GameManager    & GetManager    ();    
    // Get reference to the service.
    static inline GameGraphics   & GetGraphics   ();
    // Get pointer to the renderer.
    static inline SDL_Renderer   * GetRenderer   ();

  private:
    // Game Time service - provides access to game time.
    static GameTime       * time_       ;
    // Game Map service - provides access to the map of the game.
    static GameMap        * map_        ;
    // Game Filesystem service - provides access to loaded resources 
    // of the game: textures, map tiles - flyweight access.
    static GameFilesystem * filesystem_ ;
    // Game Auidio service - provides access to audio playing.
    static GameAudio      * audio_      ;
    // Game Manager service - provides access to game score and game modes
    // and other progress of the player in the game.
    static GameManager    * manager_    ;
    // Game Graphics service - provides access to the game screen,
    // renderer and other global graphics settings.
    static GameGraphics   * graphics_   ;
};  


inline
void GameLocator::ProvideTime (GameTime * time) {
  time_ = time;
}

inline
void GameLocator::ProvideAudio (GameAudio * audio) {
  audio_ = audio;
}

inline
void GameLocator::ProvideFilesystem (GameFilesystem * filesystem) {
  filesystem_ = filesystem;
}

inline
void GameLocator::ProvideGraphics (GameGraphics * graphics) {
  graphics_ = graphics;
}

inline
void GameLocator::ProvideManager (GameManager * manager) {
  manager_ = manager;
}

inline
void GameLocator::ProvideMap (GameMap * map) {
  map_ = map;
}

inline
GameTime & GameLocator::GetTime() {
  return * time_;
}

inline
GameAudio & GameLocator::GetAudio() {
  return * audio_;
}

inline
GameFilesystem & GameLocator::GetFilesystem() {
  return * filesystem_;
}

inline
GameGraphics & GameLocator::GetGraphics() {
  return * graphics_;
}

inline
GameManager & GameLocator::GetManager() {
  return * manager_;
}

inline
GameMap & GameLocator::GetMap() {
  return * map_;
}

inline 
SDL_Renderer * GameLocator::GetRenderer(){
  return graphics_->GetRenderer();
}