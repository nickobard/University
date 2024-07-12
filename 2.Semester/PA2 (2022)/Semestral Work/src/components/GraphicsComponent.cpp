#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(Texture *texture)
        : texture_(texture) {}

void GraphicsComponent::Render(const Vector2<float> &position) const {
    texture_->RenderTexture(position);
}

void GraphicsComponent::Render(const Vector2<float> &position, double angle) const {
    texture_->RenderTexture(position, angle);
}

void GraphicsComponent::ChangeGraphicsTexture(const string &pathOrMessage) {
    texture_->LoadTexture(pathOrMessage);
}
