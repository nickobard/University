#pragma once
#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"
/**
 * @brief Interface for all game objects in the game
 * 
 */
class GameObject {
  public:
    /**
     * @brief Make destructor virtual to allow derived classes to destruct self properly
     * 
     */
    virtual ~GameObject() = default;
    /**
     * @brief Updates the game this game object's components
     * 
     */
    virtual void Update() = 0;
      protected:
    /**
     * @brief manage destruction of this gameobject, used in destructor
     * 
     */
    virtual void FreeObject() = 0;

};