#include "Bonus.hpp"
#include "../game_engine/GameLocator.hpp"

Bonus::Bonus(GraphicsComponent *graphics)
        : graphics_(graphics) {
}

Bonus::~Bonus() {
    GameManager::ReportBonusCollection();
    GameStateNormal::AddScore(10);
    delete graphics_;
}


void Bonus::Update() {

}

void Bonus::Render(const Vector2<float> &position) {
    graphics_->Render(position);
}

void Bonus::FixedUpdate() {

}



