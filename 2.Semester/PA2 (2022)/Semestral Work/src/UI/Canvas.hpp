#pragma once

#include "UIElement.hpp"
#include <vector>
#include "../structures/Text.hpp"

using namespace std;

class Canvas : public UIElement {
public:

    Canvas(TransformComponent *transform, GraphicsComponent *graphics);

    ~Canvas() override;

    void Render() const override;

    void Render(const Vector2<float> &position) const override;

    void RenderScore() const;

    void DecreaseLives();

    void Update() override;

private:

    vector<UIElement *> livesBar_;
    Texture *livesTexture;
    int playerLives;
    pair<UIElement *, int> scoreBar_;
    Text *scoreText_;

    Vector2<float> center_;
    TextureSize<float> canvasSize_;
};