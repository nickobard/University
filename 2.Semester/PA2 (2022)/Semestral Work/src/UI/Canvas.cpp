#include "Canvas.hpp"
#include "../game_engine/GameLocator.hpp"
#include "../structures/Text.hpp"
#include <iostream>

using namespace std;

Canvas::Canvas(TransformComponent *transform, GraphicsComponent *graphics)
        : UIElement(transform, graphics)
          , playerLives(GameStateNormal::GetPlayerLives())
          , scoreBar_(nullptr, 0) {
    livesTexture = GameLocator::GetFilesystem().GetTexture(TextureType::PACMAN);
    livesBar_.push_back(
            new UIElement(new TransformComponent(Vector2<float>(230, 820)), new GraphicsComponent(livesTexture)));
    livesBar_.push_back(
            new UIElement(new TransformComponent(Vector2<float>(280, 820)), new GraphicsComponent(livesTexture)));
    livesBar_.push_back(
            new UIElement(new TransformComponent(Vector2<float>(330, 820)), new GraphicsComponent(livesTexture)));

    scoreText_ = new Text();
    scoreText_->LoadFont("assets/fonts/Minecraft.ttf", 32);
    scoreText_->LoadTexture("SCORE: " + to_string(scoreBar_.second));
    scoreBar_.first = new UIElement(new TransformComponent(Vector2<float>(20, 20)), new GraphicsComponent(scoreText_));
}

void Canvas::Render(const Vector2<float> &position) const {
    for (const auto &element: livesBar_)
        element->Render(element->GetPosition() + position);
    RenderScore();
}

void Canvas::RenderScore() const {
    auto [scoreText, scoreNumber] = scoreBar_;
    int actualScore = GameStateNormal::GetGameScore();
    if (scoreNumber != actualScore) {
        scoreNumber = actualScore;
        scoreText_->LoadTexture("SCORE: " + to_string(scoreNumber));
    }
    scoreText->Render(scoreText->GetPosition() + transform_->position_);
}

void Canvas::DecreaseLives() {
    if (!livesBar_.empty()) {
        delete livesBar_[--playerLives];
        livesBar_.erase(--livesBar_.end());
    }
}

Canvas::~Canvas() {
    for (auto obj: livesBar_)
        delete obj;
    delete scoreBar_.first;
    delete scoreText_;
}

void Canvas::Render() const {
    for (const auto *element: livesBar_)
        element->Render(element->GetPosition() + transform_->position_);
    RenderScore();
}

void Canvas::Update() {
    if (playerLives > GameStateNormal::GetPlayerLives()) {
        DecreaseLives();
    }
}


