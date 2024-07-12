#include "UIElement.hpp"

UIElement::UIElement(TransformComponent *transform, GraphicsComponent *graphics)
        : transform_(transform)
          , graphics_(graphics) {}

UIElement::~UIElement() {
    delete transform_;
    delete graphics_;
}

void UIElement::Render(const Vector2<float> &position) const {
    graphics_->Render(position);
}

void UIElement::Update() {

}

void UIElement::FixedUpdate() {

}

void UIElement::Render() const {
    graphics_->Render(transform_->position_);
}

void UIElement::ChangeGraphicsTexture(const string &pathOrMessage) {
    graphics_->ChangeGraphicsTexture(pathOrMessage);
}


