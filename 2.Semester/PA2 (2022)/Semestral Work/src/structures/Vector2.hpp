#pragma once

#include <iostream>
#include <cmath>

template<typename T_>
struct Vector2 {
    /**
     * @brief Construct a new Vector2 object.
     * @param x axis, default is 0.
     * @param y axis, default is 0.
     */
    Vector2(T_ x = 0, T_ y = 0);

    /**
     * @brief Construct a new Vector2 object
     * @tparam U_ another type of the parameter.
     * @param x axis, default is 0.
     * @param y axis, default is 0.
     */
    template<typename U_>
    Vector2(U_ x = 0, U_ y = 0);

    /**
     * @brief Copy constructor.
     */
    Vector2(const Vector2 &src);

    /**
     * @brief Copy constructor from another type.
     * Use static_cast to convert other type to this type.
     * @tparam U_ another type of the vector object used to initialize this object.
     */
    template<typename U_>
    Vector2(const Vector2<U_> &src);

    /**
     * @brief Copy-assignment constructor.
     */
    Vector2 &operator=(const Vector2 &src);

    /**
     * @brief Copy assignment constructor from another type.
     * Use static_cast to convert other type to this type.
     * @tparam U_ another type of the vector object used to assign this object.
     */
    template<typename U_>
    Vector2 &operator=(const Vector2<U_> &src);

    /// @return Vector2 object with values {0, 0}.
    static Vector2 Zero();

    /// @return Vector2 object with values {0, -1}.
    static Vector2 Up();

    /// @return Vector2 object with values {0, 1}.
    static Vector2 Down();

    /// @return Vector2 object with values {1, 0}.
    static Vector2 Right();

    /// @return Vector2 object with values {-1, 1}.
    static Vector2 Left();

    /// @return Vector2 object with values {1, 1}.
    static Vector2 One();

    /**
     * @brief Calculate absolute value of the vector object.
     * @return object with absolute values.
     */
    static Vector2 Abs(const Vector2 &src);

    /**
     * @brief Calculates distance between two vectors.
     * @return distance between two vectors.
     */
    static T_ Distance(const Vector2 &a, const Vector2 &b);

    /**
     * @brief Turn this vector to 90 degrees to the left.
     * @return Vector turned to 90 degrees to the left.
     */
    Vector2 ToLeft() const;

    /**
     * @brief Turn this vector to 90 degrees to the right.
     * @return Vector turned to 90 degrees to the right.
     */
    Vector2 ToRight() const;

    /**
     * @brief Return vector to back direction.
     * @return vector in opposite direction to current vector.
     */
    Vector2 ToBack() const;

    float ToDegrees() const;

    /**
     * @brief Converts this object form one type to another.
     * @tparam U_ type to which to convert.
     */
    template<typename U_>
    Vector2<U_> ConvertTo() const;

    // Arithmetics operators.

    template<typename U_>
    friend Vector2<U_> operator+(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    template<typename U_>
    friend Vector2<U_> operator+(const Vector2<U_> &lhs, const U_ &rhs);

    template<typename U_, typename L_>
    friend Vector2<U_> operator+(const Vector2<U_> &lhs, const L_ &rhs);

    template<typename U_>
    friend Vector2<U_> operator-(const Vector2<U_> &src);

    template<typename U_>
    friend Vector2<U_> operator-(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    template<typename U_>
    friend Vector2<U_> operator-(const Vector2<U_> &lhs, const U_ &rhs);

    template<typename U_, typename L_>
    friend Vector2<U_> operator-(const Vector2<U_> &lhs, const L_ &rhs);

    template<typename U_>
    friend Vector2<U_> operator*(const Vector2<U_> &lhs, const U_ &rhs);

    template<typename U_, typename L_>
    friend Vector2<U_> operator*(const Vector2<U_> &lhs, const L_ &rhs);

    template<typename U_>
    friend Vector2<U_> operator*(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    template<typename U_>
    friend Vector2<U_> operator/(const Vector2<U_> &lhs, const U_ &rhs);

    template<typename U_, typename L_>
    friend Vector2<U_> operator/(const Vector2<U_> &lhs, const L_ &rhs);

    template<typename U_>
    friend Vector2<U_> operator%(const Vector2<U_> &lhs, int rhs);

    // Comparison operators.

    template<typename U_>
    friend bool operator==(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    template<typename U_>
    friend bool operator!=(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    template<typename U_>
    friend bool operator<=(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    template<typename U_>
    friend bool operator>=(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    template<typename U_>
    friend bool operator<(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    template<typename U_>
    friend bool operator>(const Vector2<U_> &lhs, const Vector2<U_> &rhs);

    // Output operator.

    template<typename U_>
    friend std::ostream &operator<<(std::ostream &os, const Vector2<U_> &src);

    /// x and y axis in the 2D world
    T_ x_, y_;
};

#include "Vector2.inl"