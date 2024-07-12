#include "TransformComponent.hpp"

TransformComponent::TransformComponent()
        : direction_(Vector2<float>::Zero())
          , position_(Vector2<float>::Zero()) {}

TransformComponent::TransformComponent(const Vector2<float> &initialPosition, const Vector2<float> &direction)
        : direction_(direction)
          , position_(initialPosition) {}

TransformComponent::TransformComponent(const Vector2<float> &initialPosition)
        : direction_(Vector2<float>::Zero())
          , position_(initialPosition) {}

void TransformComponent::Translate(const Vector2<float> &newPosition) {
    position_ = newPosition;
}
