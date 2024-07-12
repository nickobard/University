#pragma once

#include "../game_objects/GameObject.hpp"

class UIElement : public GameObject {

public:

    UIElement(TransformComponent *transform, GraphicsComponent *graphics);

    ~UIElement() override;

    void Update() override;

    void FixedUpdate() override;

    virtual void Render(const Vector2<float> &position) const;

    virtual void Render() const;

    inline Vector2<float> GetPosition() const;

    void ChangeGraphicsTexture(const string &pathOrMessage);

protected:


    TransformComponent *transform_;

    GraphicsComponent *graphics_;

};

inline Vector2<float> UIElement::GetPosition() const {
    return transform_->position_;
}