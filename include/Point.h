#ifndef POINT_H
#define POINT_H

#include <type_traits>
#include <memory>
#include <iostream>

template<typename T>
concept ScalarType = std::is_scalar_v<T>;

template<ScalarType T>
class Point{
private:
    T x_;
    T y_;

public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}

    Point(const Point &other) : x_(other.x_), y_(other.y_) {}
    Point(Point &&other) noexcept : x_(std::move(other.x_)), y_(std::move(other.y_)){
        other.x_ = T(0);
        other.y_ = T(0);
    }

    Point &operator=(const Point &other){
        if (this != &other){
            x_ = other.x_;
            y_ = other.y_;
        }
        return *this;
    }
    Point &operator=(Point &&other) noexcept{
        if (this != &other){
            x_ = std::move(other.x_);
            y_ = std::move(other.y_);
            other.x_ = T(0);
            other.y_ = T(0);
        }
        return *this;
    }
    T x() const{
        return x_;
    }
    T y() const{
        return y_;
    }
    void setX(T x){
        x_ = x;
    }
    void setY(T y){
        y_ = y;
    }

    bool operator==(const Point &other) const{
        return x_ == other.x_ && y_ == other.y_;
    }
    bool operator !=(const Point &other) const{
        return !(*this == other);
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &point){
        os << "(" << point.x_ << ", " << point.y_ << ")";
        return os;
    }
    friend std::istream &operator>>(std::istream &is, Point &point){
        is >> point.x_ >> point.y_;
        return is;
    }
};
template<ScalarType T>
using PointPtr = std::unique_ptr<Point<T>>;

#endif