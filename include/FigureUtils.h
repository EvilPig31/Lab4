#ifndef FIGURUTILS_H
#define FIGURUTILS_H

#include "Figure.h"
#include "Array.h"
#include <memory>

template<ScalarType T>
double calculateTotalArea(const Array<std::shared_ptr<Figure<T>>> &figures){
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i){
        total += figures[i]->calculateArea();
    }
    return total;
}
#endif