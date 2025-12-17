#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <memory>
#include <cmath>

template<ScalarType T>
class Pentagon : public Figure<T>{
private:
    T side_;
    Point<T> center_;

public:
    Pentagon() : side_(0), center_(0, 0){}
    Pentagon(T side, T x, T y) : side_(side), center_(x, y){}
    Pentagon(T side, const Point<T> &center) : side_(side), center_(center){}
    Point<T>  calculateCenter() const override{
        return center_;
    }
    double calculateArea() const override{
        return (5.0 * side_ * side_) / (4.0 * tan(M_PI / 5.0));
    }
    std::vector<PointPtr<T>> getVertices() const override{
        std::vector<PointPtr<T>> vertices;
        vertices.reserve(5);
        double R = side_ / (2.0 * sin(M_PI / 5.0));
        for (int i = 0; i < 5; ++i){
            double angle = 2.0 * M_PI * i / 5.0 - M_PI / 2.0;
            T x = static_cast<T>(center_.x() + R * cos(angle));
            T y = static_cast<T>(center_.y() + R * sin(angle));
            vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
        return vertices;
    }
    void printVertices(std::ostream &os) const override{
        auto vertices = getVertices();
        os << "Pentagons vertices:\n";
        for (const auto &vertex : vertices){
            os << *vertex << "\n";
        }
    }
    void read(std::istream &is) override{
        std::cout << "Enter pentagon params (side, x, y)";
        is >> side_ >> center_;
    }
    bool isEqual(const Figure<T> &other) const override{
        const Pentagon *pentagon = dynamic_cast<const Pentagon*>(&other);
        if (!pentagon) return false;
        return side_ == pentagon->side_ && center_ == pentagon->center_;
    }
    Pentagon &operator=(const Pentagon &other){
        if (this != &other){
            side_ = other.side_;
            center_ = other.center_;
        }
        return *this;
    }
    bool operator==(const Pentagon &other) const{
        return isEqual(other);
    }
    T getSide() const {return side_;}
    Point<T> getCenter() const {return center_;}
};
#endif