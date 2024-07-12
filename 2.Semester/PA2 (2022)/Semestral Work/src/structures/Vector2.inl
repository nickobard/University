#pragma once
#include "Vector2.hpp"
template <typename T_>
Vector2<T_>::Vector2(T_ x, T_ y)
: x_(x)
, y_(y)
{}

template <typename T_>
Vector2<T_> Vector2<T_>::Zero(){
  return {0,0};
}

template <typename T_>
Vector2<T_> Vector2<T_>::Up(){
  return {0,1};
}

template <typename T_>
Vector2<T_> Vector2<T_>::Down(){
  return {0,-1};
}

template <typename T_>
Vector2<T_> Vector2<T_>::Right(){
  return {1,0};
}

template <typename T_>
Vector2<T_> Vector2<T_>::Left(){
  return {-1,0};
}

template <typename T_>
Vector2<T_> operator+ (const Vector2<T_> & lhs, const Vector2<T_> & rhs){
  return {lhs.x_ + rhs.x_, lhs.y_ + rhs.y_};
}

template <typename T_>
Vector2<T_> operator- ( const Vector2<T_> & src){
  return { -src.x_, -src.y_};
}

template <typename T_>
Vector2<T_> operator- (const Vector2<T_> & lhs, const Vector2<T_> & rhs){
  return lhs + (-rhs);
}

template <typename T_>
Vector2<T_> operator* (const Vector2<T_> & lhs, const T_ & rhs){
  return {lhs.x_ * rhs, lhs.y_ * rhs};
}
