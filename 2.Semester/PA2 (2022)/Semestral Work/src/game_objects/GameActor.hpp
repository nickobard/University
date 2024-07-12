#pragma once

#include "GameObject.hpp"
#include "../components/PhysicsComponent.hpp"

/// Enum to represent game actor states.
enum State {
    STANDING,
    MOVING
};

/**
 * @brief GameActor abstract class specification of the GameObject.
 *
 * Represents all gameObjects that are playable and controllable objects.
 * Are used by the controller component to control such objects using unified interface.
 * 
 */
class GameActor : public GameObject {

public:

    /**
     * @brief Construct a new Game Actor object and its components.
     * 
     * @param transform - initial transform component for the game object.
     * @param graphics - initial graphics component for the game object.
     */
    GameActor(TransformComponent *transform, GraphicsComponent *graphics, GameActor &actor);

    /**
     * @brief Destroy the Game Actor object and its components.
     */
    ~GameActor() override;

    /**
     * @brief Render object on the screen.
     */
    virtual void Render() const = 0;

    /**
     * @brief Change game object's moving direction to up.
     */
    virtual void TurnUp() = 0;

    /**
     * @brief Change game object's moving direction to down
     */
    virtual void TurnDown() = 0;

    /**
     * @brief Change game object's moving direction to right
     */
    virtual void TurnRight() = 0;

    /**
     * @brief Change game object's moving direction to left
     */
    virtual void TurnLeft() = 0;

    /**
     * @brief Change game object's moving to stop and don't move
     */
    virtual void StopMoving() = 0;

    /**
     * @brief Moves game actor in its current direction.
     */
    virtual void Move() = 0;

    /**
     * @brief Change game object's moving direction to specified direction.
     * @param direction where to turn.
     */
    virtual void TurnTo(const Vector2<float> &direction) = 0;

    /// Get the Graphics component.
    inline const GraphicsComponent *GetGraphics() const;

    /// Get the Physics component. O(1).
    inline PhysicsComponent *GetPhysics();

    inline const PhysicsComponent *GetPhysics() const;

    /// Get the Transform component.
    inline TransformComponent *GetTransform();

    inline const TransformComponent *GetTransform() const;

    /// Get velocity of the game actor.
    inline float GetVelocity() const;

    /// Set velocity of the game actor.
    inline void SetVelocity(float value);

    /// Get state of the game actor.
    inline int GetState() const;

    /// Set state of the game actor.
    inline void SetState(int value);

protected:

    /// Transform component of the game object.
    TransformComponent *transform_;
    /// Graphics component of the game object.
    GraphicsComponent *graphics_;
    /// Physics component of the game object.
    PhysicsComponent *physics_;

    /// Current game actor's velocity in the world.
    float velocity_;

    /// Represents current state of the game actor.
    int state_;

};

inline TransformComponent *GameActor::GetTransform() {
    return transform_;
}

inline const TransformComponent *GameActor::GetTransform() const {
    return transform_;
}

inline const GraphicsComponent *GameActor::GetGraphics() const {
    return graphics_;
}

inline const PhysicsComponent *GameActor::GetPhysics() const {
    return physics_;
}

inline PhysicsComponent *GameActor::GetPhysics() {
    return physics_;
}

inline float GameActor::GetVelocity() const {
    return velocity_;
}

inline void GameActor::SetVelocity(float value) {
    velocity_ = value;
}

inline int GameActor::GetState() const {
    return state_;
}

inline void GameActor::SetState(int value) {
    if (value <= MOVING)
        state_ = value;
}