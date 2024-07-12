#pragma once
/**
 * @brief Template which reperesents dimensions of the texture.
 * 
 * @tparam T_ type of the widht and height - float, int or double.
 */
template < typename T_ >
struct TextureSize{
    /**
     * @brief Construct a new Texture Size object.
     * 
     * @param w widht of the texture.
     * @param h height of the texture.
     */
    TextureSize(T_ w = 0, T_ h = 0);
    // Copy constructor.
    TextureSize(const TextureSize & src);
    // Copy assignment constructor.
    TextureSize & operator= (const TextureSize & rhs);
    // @brief Static function to get texture size with zeroed dimensions.
    static TextureSize Zero ();
    // Dimensions of the texture.
    T_ width_, height_;
};

#include "TextureSize.inl"