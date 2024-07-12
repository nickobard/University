#pragma once

#include "../structures/Vector2.hpp"

class GameObject;

/**
 * @brief Class which represents coordinates and direction in the game world.
 */
class TransformComponent {

public:

    /**
     * @brief Construct Transform component.
     */
    TransformComponent();

    /**
     * @brief Construct Transform component.
     * @param initialPosition represents initial position in the game world.
     * @param direction sets the initial direction of the object. 
     */
    TransformComponent(const Vector2<float> &initialPosition, const Vector2<float> &direction);

    /**
     * @brief Constructs Transform component.
     * @param initialPosition represents initial position in the game world.
     */
    TransformComponent(const Vector2<float> &initialPosition);

    /**
     * @brief Moves transform position to new position.
     */
    void Translate(const Vector2<float> &newPosition);

    /// direction of the gameObject which has this transform components.
    Vector2<float> direction_;

    /// current gameObject's position in the world.
    Vector2<float> position_;

};
