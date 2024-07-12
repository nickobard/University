#pragma once

/**
 * @brief Template which represents size of the texture.
 * @tparam T_ type of the width and height - float, int or double.
 */
template<typename T_>
struct TextureSize {

    /**
     * @brief Construct a new Texture Size object. O(1).
     * @param w width of the texture, default 0.
     * @param h height of the texture, default 0.
     */
    TextureSize(T_ w = 0, T_ h = 0);

    /**
     * @brief Copy constructor. O(1).
     * @param src source texture size from which construct copy of this object.
     */
    TextureSize(const TextureSize &src);

    /**
     * @brief Copy-assignment constructor. O(1).
     */
    TextureSize &operator=(const TextureSize &rhs);

    /**
     * @return texture size object with ( width = 0, height = 0 ). O(1).
     */
    static TextureSize Zero();

    // Arithmetics operators.

    template<typename U_>
    friend TextureSize<U_> operator/(const TextureSize<U_> &lhs, const U_ &rhs);

    template<typename U_, typename L_>
    friend TextureSize<U_> operator/(const TextureSize<U_> &lhs, const L_ &rhs);

    /// Size of the texture - its width and height.
    T_ width_, height_;
};

#include "TextureSize.inl"