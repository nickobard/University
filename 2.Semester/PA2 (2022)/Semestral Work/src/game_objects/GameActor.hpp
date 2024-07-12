#pragma once
#include "GameObject.hpp"
/**
 * @brief GameActor abstract class specification of the GameObject
 * 
 * Represents all gameObjects that are playabe and controllable objects
 * 
 * Are used by the controller component to control such objecs using 
 * unified interface
 * 
 */
class GameActor : public GameObject {
  public:
    /**
     * @brief Construct a new Game Actor object and its components
     * 
     * @param transform - initial transform component for the game object
     * @param graphics - initial graphics component for the game object
     */
     GameActor(TransformComponent * transform, GraphicsComponent * graphics);
     /**
      * @brief Destroy the Game Actor object using FreeObject();
      * 
      */
    ~GameActor() override;
    // Change game object's moving direction to up
    virtual void TurnUp()      = 0;
    // Change game object's moving direction to down
    virtual void TurnDown()    = 0;
    // Change game object's moving direction to right
    virtual void TurnRight()   = 0;
    // Change game object's moving direction to left
    virtual void TurnLeft()    = 0;
    // Change game object's moving to stop and don't move
    virtual void StopMoving()  = 0;
    /**
     * @brief Render this game object onto the screen
     * 
     */
    virtual void Render() = 0;
  protected:
    // Deletes transform and graphics components
    void FreeObject() override;
    // Transform component of the game object
    TransformComponent * transform_;
    // Graphics component of the game object
    GraphicsComponent * graphics_;
};