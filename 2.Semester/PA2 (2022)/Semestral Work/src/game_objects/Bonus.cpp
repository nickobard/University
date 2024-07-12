#include "Bonus.hpp"
#include "../game_engine/GameLocator.hpp"

Bonus::Bonus(GraphicsComponent *graphics)
        : graphics_(graphics) {
}

Bonus::~Bonus() {
    GameManager::ReportBonusCollection();
    delete graphics_;
}


void Bonus::Update() {

}

void Bonus::Render(const Vector2<float> &position) {
    graphics_->Render(position);
}



