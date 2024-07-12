#pragma once

#include <tuple>

#include "Vector2.hpp"

using std::tie;

template<typename T_>
Vector2<T_>::Vector2(T_ x, T_ y)
        : x_(x)
          , y_(y) {}

template<typename T_>
template<typename U_>
Vector2<T_>::Vector2(U_ x, U_ y)
        : x_(static_cast<T_>(x))
          , y_(static_cast<T_>(y)) {}

template<typename T_>
Vector2<T_>::Vector2(const Vector2<T_> &src)
        : x_(src.x_)
          , y_(src.y_) {}

template<typename T_>
template<typename U_>
Vector2<T_>::Vector2(const Vector2<U_> &src)
        : x_(static_cast<T_>(src.x_))
          , y_(static_cast<T_>(src.y_)) {}


template<typename T_>
Vector2<T_> &Vector2<T_>::operator=(const Vector2<T_> &src) {

    if (this == &src)
        return *this;

    x_ = src.x_;
    y_ = src.y_;
    return *this;
}

template<typename T_>
template<typename U_>
Vector2<T_> &Vector2<T_>::operator=(const Vector2<U_> &src) {

    x_ = static_cast<T_>(src.x_);
    y_ = static_cast<T_>(src.y_);
    return *this;
}

template<typename T_>
template<typename U_>
Vector2<U_> Vector2<T_>::ConvertTo() const {
    return {static_cast<U_>(x_), static_cast<U_>(y_)};
}

template<typename T_>
Vector2<T_> Vector2<T_>::Zero() {
    return {0, 0};
}

template<typename T_>
Vector2<T_> Vector2<T_>::Up() {
    return {0, -1};
}

template<typename T_>
Vector2<T_> Vector2<T_>::Down() {
    return {0, 1};
}

template<typename T_>
Vector2<T_> Vector2<T_>::Right() {
    return {1, 0};
}

template<typename T_>
Vector2<T_> Vector2<T_>::Left() {
    return {-1, 0};
}

template<typename T_>
Vector2<T_> Vector2<T_>::One() {
    return {1, 1};
}

template<typename T_>
Vector2<T_> operator+(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return {lhs.x_ + rhs.x_, lhs.y_ + rhs.y_};
}

template<typename U_>
Vector2<U_> operator+(const Vector2<U_> &lhs, const U_ &rhs) {
    return {lhs.x_ + rhs, lhs.y_ + rhs};
}

template<typename U_, typename L_>
Vector2<U_> operator+(const Vector2<U_> &lhs, const L_ &rhs) {
    return {lhs.x_ + static_cast<U_>(rhs),
            lhs.y_ + static_cast<U_>(rhs)};
}

template<typename T_>
Vector2<T_> operator-(const Vector2<T_> &src) {
    return {-src.x_, -src.y_};
}

template<typename T_>
Vector2<T_> operator-(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return lhs + (-rhs);
}

template<typename U_>
Vector2<U_> operator-(const Vector2<U_> &lhs, const U_ &rhs) {
    return {lhs.x_ - rhs, lhs.y_ - rhs};
}

template<typename T_>
Vector2<T_> operator*(const Vector2<T_> &lhs, const T_ &rhs) {
    return {lhs.x_ * rhs, lhs.y_ * rhs};
}

template<typename T_>
Vector2<T_> operator*(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return {lhs.x_ * rhs.x_, lhs.y_ * rhs.y_};
}

template<typename T_, typename U_>
Vector2<T_> operator*(const Vector2<T_> &lhs, const U_ &rhs) {
    return {lhs.x_ * static_cast<T_>(rhs),
            lhs.y_ * static_cast<T_>(rhs)};
}

template<typename U_, typename L_>
Vector2<U_> operator-(const Vector2<U_> &lhs, const L_ &rhs) {
    return {lhs.x_ - static_cast<U_>(rhs),
            lhs.y_ - static_cast<U_>(rhs)};
}

template<typename T_>
Vector2<T_> operator/(const Vector2<T_> &lhs, const T_ &rhs) {
    return {lhs.x_ / rhs, lhs.y_ / rhs};
}

template<typename T_, typename U_>
Vector2<T_> operator/(const Vector2<T_> &lhs, const U_ &rhs) {
    return {lhs.x_ / static_cast<T_>(rhs),
            lhs.y_ / static_cast<T_>(rhs)};
}

template<typename T_>
bool operator==(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return tie(lhs.x_, lhs.y_) == tie(rhs.x_, rhs.y_);
}

template<typename T_>
bool operator!=(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return tie(lhs.x_, lhs.y_) != tie(rhs.x_, rhs.y_);
}

template<typename T_>
bool operator<(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return tie(lhs.x_, lhs.y_) < tie(rhs.x_, rhs.y_);
}

template<typename T_>
bool operator<=(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return tie(lhs.x_, lhs.y_) <= tie(rhs.x_, rhs.y_);
}

template<typename T_>
bool operator>=(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return tie(lhs.x_, lhs.y_) >= tie(rhs.x_, rhs.y_);
}

template<typename T_>
bool operator>(const Vector2<T_> &lhs, const Vector2<T_> &rhs) {
    return tie(lhs.x_, lhs.y_) > tie(rhs.x_, rhs.y_);;
}

template<typename T_>
std::ostream &operator<<(std::ostream &os, const Vector2<T_> &src) {
    os << "{ " << src.x_ << " " << src.y_ << " }";
    return os;
}

template<typename U_>
Vector2<U_> operator%(const Vector2<U_> &lhs, int rhs) {
    return {lhs.x_ % rhs, lhs.y_ % rhs};
}

template<typename T_>
Vector2<T_> Vector2<T_>::Abs(const Vector2<T_> &src) {
    return {src.x_ < 0 ? -src.x_ : src.x_, src.y_ < 0 ? -src.y_ : src.y_};
}

template<typename T_>
Vector2<T_> Vector2<T_>::ToLeft() const {
    return {y_, -x_};
}

template<typename T_>
Vector2<T_> Vector2<T_>::ToRight() const {
    return {-y_, x_};
}

template<typename T_>
T_ Vector2<T_>::Distance(const Vector2<T_> &a, const Vector2<T_> &b) {
    Vector2<T_> c(a - b);
    return hypot(c.x_, c.y_);
}

template<typename T_>
Vector2<T_> Vector2<T_>::ToBack() const {
    return {-x_, -y_};
}

template<typename T_>
float Vector2<T_>::ToDegrees() const {
    return atan2(y_, x_) * 180 / M_PI;
}
