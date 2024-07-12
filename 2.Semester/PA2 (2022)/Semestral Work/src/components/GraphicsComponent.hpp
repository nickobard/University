#pragma once
#include "../structures/Texture.hpp"

class GraphicsComponent {
  public:
    /**
     * @brief Construct a new Graphics Component object
     * 
     * @param texture - texture provided by the filesystem
     */
    GraphicsComponent(Texture * texture);
    virtual ~GraphicsComponent () = default;
    /**
     * @brief Render image each game frame onto the screen
     * 
     * @param position - position where to render on the screen in pixels
     */
    virtual void Render(Vector2<float> position);
  private:
    // Texture to be set up and rendered
    Texture * texture_;
};