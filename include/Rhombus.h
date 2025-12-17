#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <cmath>
#include <memory>

template<ScalarType T>
class Rhombus : public Figure<T>{
private:
    T diagonal1_;
    T diagonal2_;
    Point<T> center_;

public:
    Rhombus() : diagonal1_(0), diagonal2_(0), center_(0, 0){}
    Rhombus(T d1, T d2, T x, T y) : diagonal1_(d1), diagonal2_(d2), center_(x, y){}
    Rhombus(T d1, T d2, const Point<T> &center) : diagonal1_(d1), diagonal2_(d2), center_(center){}
    Rhombus(const Rhombus &other) : diagonal1_(other.diagonal1_), diagonal2_(other.diagonal2_), center_(other.center_){}
    Rhombus(Rhombus &&other) noexcept : diagonal1_(std::move(other.diagonal1_)), diagonal2_(std::move(other.diagonal2_)), center_(std::move(other.center_)){
        other.diagonal1_ = T(0);
        other.diagonal2_ = T(0);
    }
    Point<T>  calculateCenter() const override{
        return center_;
    }
    double calculateArea() const override{
        return static_cast<double>(diagonal1_ * diagonal2_) / 2.0;
    }
    std::vector<PointPtr<T>> getVertices() const override{
        std::vector<PointPtr<T>> vertices;
        vertices.reserve(4);
        T half_d1 = diagonal1_ / 2;
        T half_d2 = diagonal2_ / 2;
        vertices.push_back(std::make_unique<Point<T>>(
            center_.x(), center_.y() + half_d2));
        vertices.push_back(std::make_unique<Point<T>>(
            center_.x() + half_d1, center_.y()));
        vertices.push_back(std::make_unique<Point<T>>(
            center_.x(), center_.y() - half_d2));
        vertices.push_back(std::make_unique<Point<T>>(
            center_.x() - half_d1, center_.y()));
        return vertices;
    }
    void printVertices(std::ostream &os) const override{
        auto vertices = getVertices();
        os << "Rhombus vertices:\n";
        for (const auto &vertex : vertices){
            os << *vertex << "\n";
        }
    }
    void read(std::istream &is) override{
        std::cout << "Enter rhombus params (diagonal1, diagonal2 x, y)";
        is >> diagonal1_ >> diagonal2_ >> center_;
    }
    bool isEqual(const Figure<T> &other) const override{
        const Rhombus *rhombus = dynamic_cast<const Rhombus*>(&other);
        if (!rhombus) return false;
        return diagonal1_ == rhombus->diagonal1_ && diagonal2_ == rhombus->diagonal2_ && center_ == rhombus->center_;
    }
    Rhombus &operator=(const Rhombus &other){
        if (this != &other){
            diagonal1_ = other.diagonal1_;
            diagonal2_ = other.diagonal2_;
            center_ = other.center_;
        }
        return *this;
    }
    Rhombus &operator=(Rhombus &&other) noexcept {
        if(this != &other) {
            diagonal1_ = std::move(other.diagonal1_);
            diagonal2_ = std::move(other.diagonal2_);
            center_ = std::move(other.center_);
            other.diagonal1_ = T(0);
            other.diagonal2_= T(0);
        }
        return *this;
    }
    bool operator==(const Rhombus &other) const{
        return isEqual(other);
    }
    T getDiagonal1() const {return diagonal1_;}
    T getDiagonal2() const {return diagonal2_;}
    Point<T> getCenter() const {return center_;}
};
#endif