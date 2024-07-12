#pragma once

#include "TextureSize.hpp"

template<typename T_>
TextureSize<T_>::TextureSize(T_ w, T_ h)
        : width_(w)
          , height_(h) {}

template<typename T_>
TextureSize<T_>::TextureSize(const TextureSize<T_> &src)
        : width_(src.width_)
          , height_(src.height_) {}

template<typename T_>
TextureSize<T_> &TextureSize<T_>::operator=(const TextureSize<T_> &rhs) {
    if (this == &rhs)
        return *this;
    width_ = rhs.width_;
    height_ = rhs.height_;
    return *this;
}

template<typename T_>
TextureSize<T_> TextureSize<T_>::Zero() {
    return {0, 0};
}

template<typename T_>
TextureSize<T_> operator/(const TextureSize<T_> &lhs, const T_ &rhs) {
    return {lhs.width_ / rhs, lhs.height_ / rhs};
}

template<typename T_, typename U_>
TextureSize<T_> operator/(const TextureSize<T_> &lhs, const U_ &rhs) {
    return {lhs.width_ / static_cast<T_>(rhs), lhs.height_ / static_cast<T_>(rhs)};

}




