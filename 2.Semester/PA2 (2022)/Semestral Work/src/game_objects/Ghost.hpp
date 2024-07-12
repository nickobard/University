#pragma once

#include "GameActor.hpp"

/**
 * @brief Pacman class - concrete specification of the GameActor,
 * which defines its moving algorithms and what it does.
 */
class Ghost : public GameActor {

public:

    /**
     * @brief Ghost constructor - takes components to construct ghost object.
     * @param transform transform component of the object.
     * @param graphics graphics component of the object.
     */
    Ghost(TransformComponent *transform, GraphicsComponent *graphics);

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

private:

    void CheckTunnel();

};