#pragma once
#include "../structures/Vector2.hpp"
#include "../game_engine/GameLocator.hpp"
#include "../game_engine/GameGraphics.hpp"

/**
 * @brief Forward declaration of the GameObjct class which
 * indirectly uses this component.
 * 
 */
class GameObject;

/**
 * @brief Enum to identifiy the direction of the gameObject
 * 
 */
enum Directions {

  UP, DOWN, RIGHT, LEFT  

};

/**
 * @brief Class which represents coordinates and move in the game world.
 * 
 */
class TransformComponent{

  public:

    /**
     * @brief Initialize transform component with zeros and UP direction
     * 
     */
    TransformComponent();


    /**
     * @brief Construct a new Transform object.
     *
     * @param initialPosition creates object with given position in the world.
     * @param direction sets the initial direction of the object. 
     * Default is UP if no direction provided.
     */
    TransformComponent(Vector2<float> initialPosition, int direction );


    /**
     * @brief Destroy the Transform object - virtual for any derived.
     * 
     */
    virtual ~TransformComponent();


    /**
     * @brief Gets current transform position, used for passing to other
     * components , like graphics to render at same place.
     * 
     * @return Vector2<float> current position of the game object.
     */
    inline Vector2<float> GetPosition();


    /**
     * @brief Translates object to the direction with given velocity.
     * 
     * @param velocity velocity with which object will be translated
     * instead of default game speed.
     */
    void Translate(const float & velocity);
    

    /**
     * @brief Translates object to the directions with its set velocity.
     * 
     */
    void Translate();    


    /** @brief Set the Direction object.
     *
     * @details Checks if input is valid and changes the velocity of the
     * transform component.
     *
     * @param value enum value for new direction of the object
     */
    void SetDirection (const int value);


    /**
     * @brief Sets the velocity to the new value.
     * 
     * @param value new velocity for the game object.
     */
    inline void SetVelocity ( const float & value );


    /**
     * @brief Resets transform velocit to default GAME_SPEED value.
     * 
     */
    inline void SetDefaultVelocity ();

  protected:

    // Represents default game speed. 
    static constexpr float GAME_SPEED = 200.0f;

    // direction of the gameObject which has this transform components.
    Vector2<float> direction_;

    // current gameObject's position in the world.
    Vector2<float> position_;

    // current gameObject's velocity in the world.
    float velocity_;
};

inline
Vector2<float> TransformComponent::GetPosition(){
  return position_;
}

inline 
void TransformComponent::SetVelocity( const float & value){
  velocity_ = value;
}

inline 
void TransformComponent::SetDefaultVelocity (){
  velocity_ = GAME_SPEED;
}
