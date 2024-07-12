#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(Texture * texture)
: texture_(texture)
{}

void GraphicsComponent::Render(Vector2<float> position){
  texture_->RenderTexture(position);
}