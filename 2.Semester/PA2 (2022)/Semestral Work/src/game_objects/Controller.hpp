#pragma once
#include "GameObject.hpp"
#include "../components/ControllerComponent.hpp"
/**
 * @brief Game Object subclass which controls game actor objects
 * Uses controller component, like InputComponent or AIComponent
 * 
 */
class Controller : public GameObject{
  public:
    // Constructs controller with given type of the controller.
    Controller(ControllerComponent * controller)
    : controller_(controller)
    {}
    // Frees its components with FreeObject() methods
    ~Controller(){
      FreeObject();
    }
    // Update itself - updating the given controller
    void Update() override{
      controller_->Update();
    }
  private:
    // Deletes controller
    void FreeObject() override{
      delete controller_;
    }
    // Controller component
    ControllerComponent * controller_;
};