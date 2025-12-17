#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include <memory>
#include <iostream>
#include "Point.h"

template<ScalarType T>
class Figure{
public:
    virtual ~Figure() = default;
    virtual double calculateArea() const = 0;
    virtual Point<T> calculateCenter() const = 0;
    virtual std::vector<PointPtr<T>> getVertices() const = 0;;
    virtual void printVertices(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;
    virtual bool isEqual(const Figure &other) const = 0;
    explicit operator double() const{
        return calculateArea();
    }
};
template<ScalarType T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &figure){
    figure.printVertices(os);
    return os;
}
template<ScalarType T>
std::istream &operator>>(std::istream &is, Figure<T> &figure){
    figure.read(is);
    return is;
}
#endif