#pragma once
#include "GameActor.hpp"
/**
 * @brief Pacman class - concrete specification of the GameActor,
 * which defines its moving algorithms and what it does.
 * 
 */
class Pacman : public GameActor {
  public:
    // Pacman constructor - takes components to construct GameActor abstract class
    Pacman (TransformComponent * transform, GraphicsComponent * graphics);
    // Default destructor - destruction is already handled in the GameActor abstract class
    ~Pacman() override = default;
    // Change game object's moving direction to up
    void TurnUp()      override;
    // Change game object's moving direction to down
    void TurnDown()    override;
    // Change game object's moving direction to right
    void TurnRight()   override;
    // Change game object's moving direction to left
    void TurnLeft()    override;
    // Change game object's moving to stop and don't move
    void StopMoving()  override;

    // Update function to update state of this gameObject
    void Update() override;
    // Render function to render this object using its transform position
    void Render() override;
};