#pragma once

#include "GameActor.hpp"

/**
 * @brief Pacman class - concrete specification of the GameActor,
 * which defines its moving algorithms and what it does.
 */
class Pacman : public GameActor {

public:

    /**
     * @brief Pacman constructor - takes components to construct pacman object. O(1).
     * @param transform transform component of the object.
     * @param graphics graphics component of the object.
     */
    Pacman(TransformComponent *transform, GraphicsComponent *graphics);

    void TurnUp() override;

    void TurnDown() override;

    void TurnRight() override;

    void TurnLeft() override;

    void StopMoving() override;

    void Move() override;

    void TurnTo(const Vector2<float> &direction) override;

    void Update() override;

    void FixedUpdate() override;

    void Render() const override;

    /**
     * @brief Change direction if there are no possible
     * collisions with other game objects. O(1).
     * @param direction new direction of the game object.
     */
    void TryChangeDirection(const Vector2<float> &newDirection);

    /**
     * @brief Collects bonus on the current tile node.
     */
    void CollectBonus();

};