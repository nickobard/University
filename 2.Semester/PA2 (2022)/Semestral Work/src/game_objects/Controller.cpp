#include "Controller.hpp"

Controller::Controller(ControllerComponent *controller)
        : controller_(controller)
          , state_(Controller::ENABLED) {}

Controller::~Controller() {
    delete controller_;
}

void Controller::Update() {
    if (state_ == ENABLED)
        controller_->Update();
}