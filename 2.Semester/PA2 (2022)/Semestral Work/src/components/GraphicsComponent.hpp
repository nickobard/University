#pragma once

#include "../structures/Texture.hpp"

class GraphicsComponent {

public:

    /**
     * @brief Construct a new Graphics Component object. O(1).
     * @param texture - texture provided by the filesystem.
     */
    explicit GraphicsComponent(Texture *texture);

    /**
     * @brief Destruct graphics component. O(1).
     */
    virtual ~GraphicsComponent() = default;

    void ChangeGraphicsTexture(const string &pathOrMessage);

    /**
     * @brief Render image each game frame onto the screen. O(1).
     * @param position - position where to render on the screen in pixels.
     */
    virtual void Render(const Vector2<float> &position) const;

    virtual void Render(const Vector2<float> &position, double angle) const;

    /**
     * @brief Get the size of the texture graphics component is holding. O(1).
     * @return reference to const texture size.
     */
    inline const TextureSize<float> &GetTextureSize() const;

private:

    /// Texture of the game object.
    Texture *texture_;

};

inline const TextureSize<float> &GraphicsComponent::GetTextureSize() const {
    return texture_->GetSize();
}