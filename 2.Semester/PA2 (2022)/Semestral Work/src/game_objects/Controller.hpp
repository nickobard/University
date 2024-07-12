#pragma once

#include "GameObject.hpp"
#include "../components/ControllerComponent.hpp"

/**
 * @brief Game Object subclass which controls game actor objects.
 * Uses controller component which controls assigned game actor to it.
 */
class Controller : public GameObject {

public:

    enum State {
        ENABLED,
        DISABLED
    };

    /**
     * @brief Construct this controller object.
     * @param controller component which defines controller behavior.
     */
    explicit Controller(ControllerComponent *controller);

    /**
     * @brief Destructor - destroys controller and its components.
     */
    ~Controller() override;

    void Update() override;

    /// Get controller component.
    inline ControllerComponent *GetController();

    /// Set controller state.
    inline void SetState(int value);

private:

    /// Controller component.
    ControllerComponent *controller_;

    /// States of the controller
    int state_;

};

inline ControllerComponent *Controller::GetController() {
    return controller_;
}

inline void Controller::SetState(int value) {
    if (value <= DISABLED)
        state_ = value;
}
