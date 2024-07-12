#pragma once

#include "GameObject.hpp"

/**
 * @brief Class that represents bonus game object.
 */
class Bonus : public GameObject {

public:

    /**
     * @brief Constructs bonus game object.
     * @param graphics component of the bonus game object.
     */
    explicit Bonus(GraphicsComponent *graphics);

    ~Bonus() override;

    void Update() override;

    /**
     * @brief Shows bonus graphics on the screen each frame.
     * @param position of the tile where this bonus attached.
     */
    void Render(const Vector2<float> &position);

private:

    /// Graphics component of the bonus game object.
    GraphicsComponent *graphics_;

};