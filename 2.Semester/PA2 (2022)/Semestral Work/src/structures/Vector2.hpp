#pragma once

template <typename T_>
struct Vector2{
  /**
   * @brief Construct a new Vector 2 object
   * 
   * @param x - x axis, default is 0
   * @param y - y axis, default is 0
   */
  Vector2(T_ x = 0, T_ y = 0);
  /**
   * @brief Provides point with zero coordinates
   * 
   * @return Vector2 with x and y set to 0.0f
   */
  static Vector2 Zero();
  /// @return Vector2 object with y set up to  1.
  static Vector2 Up();
  /// @return Vector2 object with y set up to -1.
  static Vector2 Down();
  /// @return Vector2 object with x set up to  1.
  static Vector2 Right();
  /// @return Vector2 object with x set up to -1.
  static Vector2 Left();
  
  // operator to sum vectors
  template<typename U_>
  friend Vector2<U_> operator+ (const Vector2<U_> & lhs, const Vector2<U_> & rhs);
  // unary operator to negate vector's value
  template<typename U_>
  friend Vector2<U_> operator- (const Vector2<U_> & src);
  // minus operator to substract vectors. Uses combination of sum and negate opeartors
  template<typename U_>
  friend Vector2<U_> operator- (const Vector2<U_> & lhs, const Vector2<U_> & rhs);
  // multiply by constant value operator
  template<typename U_>
  friend Vector2<U_> operator* (const Vector2<U_> & lhs, const U_ & rhs);

  // x and y axis in the 2D world
  T_ x_, y_;
};

#include "Vector2.inl"