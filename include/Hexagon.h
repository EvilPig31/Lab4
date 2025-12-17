#ifndef HEXAGON_H
#define HEXAGON_H

#include "Figure.h"
#include <memory>
#include <cmath>

template<ScalarType T>
class Hexagon : public Figure<T>{
private:
    T side_;
    Point<T> center_;

public:
    Hexagon() : side_(0), center_(0, 0){}
    Hexagon(T side, T x, T y) : side_(side), center_(x, y){}
    Point<T>  calculateCenter() const override{
        return center_;
    }
    double calculateArea() const override{
        return (3.0 * sqrt(3.0) * side_ * side_) / 2.0;
    }
    std::vector<PointPtr<T>> getVertices() const override{
        std::vector<PointPtr<T>> vertices;
        vertices.reserve(6);
        T R = side_;
        for (int i = 0; i < 6; ++i){
            double angle = 2.0 * M_PI * i / 6.0;
            T x = static_cast<T>(center_.x() + R * cos(angle));
            T y = static_cast<T>(center_.y() + R * sin(angle));
            vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
        return vertices;
    }
    void printVertices(std::ostream &os) const override{
        auto vertices = getVertices();
        os << "Hetagon vertices:\n";
        for (const auto &vertex : vertices){
            os << *vertex << "\n";
        }
    }
    void read(std::istream &is) override{
        std::cout << "Enter hexagon params (side, x, y)";
        is >> side_ >> center_;
    }
    bool isEqual(const Figure<T> &other) const override{
        const Hexagon *hexagon = dynamic_cast<const Hexagon*>(&other);
        if (!hexagon) return false;
        return side_ == hexagon->side_ && center_ == hexagon->center_;
    }
    Hexagon &operator=(const Hexagon &other){
        if (this != &other){
            side_ = other.side_;
            center_ = other.center_;
        }
        return *this;
    }
    bool operator==(const Hexagon &other) const{
        return isEqual(other);
    }
    T getSide() const {return side_;}
    Point<T> getCenter() const {return center_;}
};
#endif