#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(Texture *texture)
        : texture_(texture) {}

void GraphicsComponent::Render(const Vector2<float> &position) const {
    texture_->RenderTexture(position);
}