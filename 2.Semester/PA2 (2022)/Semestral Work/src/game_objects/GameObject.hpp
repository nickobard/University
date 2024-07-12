#pragma once

#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"

/**
 * @brief Interface for all game objects in the game
 */
class GameObject {

public:
    /**
     * @brief Default destructor of the game object.
     */
    virtual ~GameObject() = default;

    /**
     * @brief Updates this game object in the game.
     */
    virtual void Update() = 0;

};