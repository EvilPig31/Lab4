#include "../include/Rhombus.h"
#include "../include/Hexagon.h"
#include "../include/Pentagon.h"
#include "../include/Array.h"
#include "../include/Point.h"
#include "../include/Figure.h"
#include "../include/FigureUtils.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

TEST(test_1, PointConstruct){
    Point<int> p;
    EXPECT_EQ(p.x(), 0);
    EXPECT_EQ(p.y(), 0);
}

TEST(test_1, PointDefaultConstruct) {
    Point<int> p;
    EXPECT_EQ(p.x(), 0);
    EXPECT_EQ(p.y(), 0);
}

TEST(test_2, PointParamConstruct) {
    Point<double> p(3.5, 2.7);
    EXPECT_DOUBLE_EQ(p.x(), 3.5);
    EXPECT_DOUBLE_EQ(p.y(), 2.7);
}

TEST(test_3, PointCopyConstruct) {
    Point<float> p1(1.1f, 2.2f);
    Point<float> p2(p1);
    EXPECT_FLOAT_EQ(p2.x(), 1.1f);
    EXPECT_FLOAT_EQ(p2.y(), 2.2f);
}

TEST(test_4, PointMoveConstruct) {
    Point<int> p1(10, 20);
    Point<int> p2(std::move(p1));
    EXPECT_EQ(p2.x(), 10);
    EXPECT_EQ(p2.y(), 20);
}

TEST(test_5, PointAssignment) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(3.0, 4.0);
    
    p2 = p1;
    EXPECT_DOUBLE_EQ(p2.x(), 1.0);
    EXPECT_DOUBLE_EQ(p2.y(), 2.0);
}

TEST(test_7, PointEquality) {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(3, 4);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(test_8, PointInequality) {
    Point<int> p1(1, 2);
    Point<int> p2(3, 4);
    
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != Point<int>(1, 2));
}


TEST(test_15, RhombusDefaultConstruct) {
    Rhombus<double> r;
    auto center = r.calculateCenter();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
    EXPECT_DOUBLE_EQ(r.calculateArea(), 0.0);
}

TEST(test_16, RhombusParamConstruct) {
    Rhombus<double> r(8.0, 6.0, 2.0, 3.0);
    auto center = r.calculateCenter();
    EXPECT_DOUBLE_EQ(center.x(), 2.0);
    EXPECT_DOUBLE_EQ(center.y(), 3.0);
}

TEST(test_17, RhombusAreaCalc) {
    Rhombus<double> r1(8.0, 6.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(r1.calculateArea(), 24.0);
    
    Rhombus<double> r2(4.0, 5.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(r2.calculateArea(), 10.0);
}

TEST(test_18, RhombusVertices) {
    Rhombus<double> r(4.0, 6.0, 0.0, 0.0);
    auto vertices = r.getVertices();
    
    EXPECT_EQ(vertices.size(), 4);
    EXPECT_DOUBLE_EQ(vertices[0]->x(), 0.0);
    EXPECT_DOUBLE_EQ(vertices[0]->y(), 3.0);
}

TEST(test_19, RhombusIsEqual) {
    Rhombus<double> r1(4.0, 5.0, 1.0, 1.0);
    Rhombus<double> r2(4.0, 5.0, 1.0, 1.0);
    Rhombus<double> r3(4.0, 5.0, 2.0, 2.0);
    
    EXPECT_TRUE(r1.isEqual(r2));
    EXPECT_FALSE(r1.isEqual(r3));
}


TEST(test_23, RhombusDifferentTypes) {
    Rhombus<int> r1(6, 8, 0, 0);
    EXPECT_DOUBLE_EQ(r1.calculateArea(), 24.0);
    
    Rhombus<float> r2(4.0f, 5.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(r2.calculateArea(), 10.0f);
}


TEST(test_24, PentagonDefaultConstruct) {
    Pentagon<double> p;
    auto center = p.calculateCenter();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
    EXPECT_DOUBLE_EQ(p.calculateArea(), 0.0);
}

TEST(test_25, PentagonAreaCalc) {
    Pentagon<double> p(1.0, 0.0, 0.0);
    double expected = (5.0 * 1.0 * 1.0) / (4.0 * tan(M_PI / 5.0));
    EXPECT_NEAR(p.calculateArea(), expected, 1e-10);
}

TEST(test_26, PentagonVerticesCount) {
    Pentagon<double> p(2.0, 0.0, 0.0);
    auto vertices = p.getVertices();
    EXPECT_EQ(vertices.size(), 5);
}

TEST(test_27, PentagonIsEqual) {
    Pentagon<double> p1(3.0, 1.0, 1.0);
    Pentagon<double> p2(3.0, 1.0, 1.0);
    Pentagon<double> p3(4.0, 1.0, 1.0);
    
    EXPECT_TRUE(p1.isEqual(p2));
    EXPECT_FALSE(p1.isEqual(p3));
}


TEST(test_35, FigurePointerPolymorphism) {
    unique_ptr<Figure<double>> figure;
    
    figure = make_unique<Rhombus<double>>(4.0, 5.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(figure->calculateArea(), 10.0);
    
    figure = make_unique<Pentagon<double>>(1.0, 0.0, 0.0);
    double pentagonArea = (5.0 * 1.0) / (4.0 * tan(M_PI / 5.0));
    EXPECT_NEAR(figure->calculateArea(), pentagonArea, 1e-10);
}


TEST(test_37, PolymorphicArray) {
    vector<shared_ptr<Figure<double>>> figures;
    
    figures.push_back(make_shared<Rhombus<double>>(4.0, 5.0, 0.0, 0.0));
    figures.push_back(make_shared<Pentagon<double>>(1.0, 0.0, 0.0));
    
    double totalArea = 0.0;
    for (const auto& figure : figures) {
        totalArea += figure->calculateArea();
    }
    
    EXPECT_GT(totalArea, 0.0);
}


TEST(test_38, TotalAreaEmpty) {
    Array<shared_ptr<Figure<double>>> figures;
    EXPECT_DOUBLE_EQ(calculateTotalArea(figures), 0.0);
}

TEST(test_39, TotalAreaSingleFigure) {
    Array<shared_ptr<Figure<double>>> figures;
    figures.push_back(make_shared<Rhombus<double>>(4.0, 5.0, 0.0, 0.0));
    EXPECT_DOUBLE_EQ(calculateTotalArea(figures), 10.0);
}

TEST(test_40, TotalAreaMultipleFigures) {
    Array<shared_ptr<Figure<double>>> figures;
    
    figures.push_back(make_shared<Rhombus<double>>(4.0, 5.0, 0.0, 0.0));
    
    double pentagonArea = (5.0 * 1.0) / (4.0 * tan(M_PI / 5.0));
    figures.push_back(make_shared<Pentagon<double>>(1.0, 0.0, 0.0));
    
    double expectedTotal = 10.0 + pentagonArea;
    EXPECT_NEAR(calculateTotalArea(figures), expectedTotal, 1e-10);
}

TEST(test_41, ArrayDefaultConstruct) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(test_42, ArraySizeConstruct) {
    Array<double> arr(5);
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr.capacity(), 5);
    EXPECT_FALSE(arr.empty());
}

TEST(test_43, ArrayInitializerList) {
    Array<int> arr = {1, 2, 3, 4, 5};
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[4], 5);
}

TEST(test_44, ArrayCopyConstruct) {
    Array<int> arr1 = {1, 2, 3};
    Array<int> arr2(arr1);
    
    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[2], 3);
}

TEST(test_45, ArrayMoveConstruct) {
    Array<int> arr1 = {1, 2, 3};
    Array<int> arr2(std::move(arr1));
    
    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(test_46, ArrayPushBack) {
    Array<int> arr;
    
    arr.push_back(1);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 1);
    
    arr.push_back(2);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 2);
}

TEST(test_47, ArrayRemove) {
    Array<int> arr = {1, 2, 3, 4, 5};
    
    arr.remove(2);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 5);
}

TEST(test_48, ArrayClear) {
    Array<int> arr = {1, 2, 3, 4, 5};
    arr.clear();
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(test_49, ArrayAccessOperator) {
    Array<double> arr = {1.1, 2.2, 3.3};
    
    EXPECT_DOUBLE_EQ(arr[0], 1.1);
    EXPECT_DOUBLE_EQ(arr[1], 2.2);
    EXPECT_DOUBLE_EQ(arr[2], 3.3);
    
    arr[1] = 9.9;
    EXPECT_DOUBLE_EQ(arr[1], 9.9);
}

TEST(test_50, ArrayOutOfBounds) {
    Array<int> arr = {1, 2, 3};
    
    EXPECT_THROW(arr[10], std::out_of_range);
    EXPECT_THROW(arr[-1], std::out_of_range);
}

TEST(test_51, ArrayIterators) {
    Array<int> arr = {1, 2, 3, 4, 5};
    
    int sum = 0;
    for (int value : arr) {
        sum += value;
    }
    EXPECT_EQ(sum, 15);
}


TEST(test_52, ArrayOfRawPointersToFigure) {
    Array<Figure<int>*> figures;
    
    figures.push_back(new Rhombus<int>(6, 8, 0, 0));
    figures.push_back(new Pentagon<int>(5, 0, 0));
    
    EXPECT_EQ(figures.size(), 2);
    
    double totalArea = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        totalArea += figures[i]->calculateArea();
    }
    
    EXPECT_GT(totalArea, 0.0);
    
    for (size_t i = 0; i < figures.size(); ++i) {
        delete figures[i];
    }
}

TEST(test_53, ArrayOfSpecificDerivedType) {

    Array<Rhombus<int>> rhombuses;
    
    rhombuses.push_back(Rhombus<int>(4, 5, 0, 0));
    rhombuses.push_back(Rhombus<int>(6, 8, 1, 1));
    rhombuses.push_back(Rhombus<int>(10, 12, 2, 2));
    
    EXPECT_EQ(rhombuses.size(), 3);
    
    int squareCount = 0;
    for (size_t i = 0; i < rhombuses.size(); ++i) {
        EXPECT_GT(rhombuses[i].calculateArea(), 0.0);
    }
    
}


TEST(test_55, ArrayCopyAndMoveOperations) {
    Array<shared_ptr<Figure<double>>> original;
    original.push_back(make_shared<Rhombus<double>>(4.0, 5.0, 0.0, 0.0));
    original.push_back(make_shared<Pentagon<double>>(3.0, 1.0, 1.0));
    
    Array<shared_ptr<Figure<double>>> copied = original;
    EXPECT_EQ(original.size(), copied.size());
    
    Array<shared_ptr<Figure<double>>> moved = std::move(original);
    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(moved.size(), 2);
}

TEST(test_56, CompleteWorkflowDemonstration) {
    Array<shared_ptr<Figure<double>>> figures;
    
    figures.push_back(make_shared<Rhombus<double>>(8.0, 6.0, 2.0, 3.0));
    figures.push_back(make_shared<Pentagon<double>>(5.0, 0.0, 0.0));
    figures.push_back(make_shared<Hexagon<double>>(4.0, 1.0, 1.0));
    
    for (size_t i = 0; i < figures.size(); ++i) {
        auto center = figures[i]->calculateCenter();
        double area = figures[i]->calculateArea();
        EXPECT_GT(area, 0.0);
    }
    
    double totalArea = calculateTotalArea(figures);
    EXPECT_GT(totalArea, 0.0);
    
    size_t originalSize = figures.size();
    if (!figures.empty()) {
        figures.remove(0);
        EXPECT_EQ(figures.size(), originalSize - 1);
    }
}

TEST(test_57, DifferentScalarTypes) {
    Array<shared_ptr<Figure<int>>> intFigures;
    intFigures.push_back(make_shared<Rhombus<int>>(4, 5, 0, 0));
    EXPECT_EQ(intFigures.size(), 1);
    
    Array<shared_ptr<Figure<double>>> doubleFigures;
    doubleFigures.push_back(make_shared<Rhombus<double>>(4.5, 5.5, 0.0, 0.0));
    EXPECT_EQ(doubleFigures.size(), 1);
    
    Array<shared_ptr<Figure<float>>> floatFigures;
    floatFigures.push_back(make_shared<Rhombus<float>>(4.5f, 5.5f, 0.0f, 0.0f));
    EXPECT_EQ(floatFigures.size(), 1);
}

TEST(test_58, AllRequiredFigures) {
    Rhombus<double> rhombus(6.0, 8.0, 0.0, 0.0);
    Pentagon<double> pentagon(3.0, 1.0, 1.0);
    Hexagon<double> hexagon(4.0, 2.0, 2.0);
    
    EXPECT_GT(rhombus.calculateArea(), 0.0);
    EXPECT_GT(pentagon.calculateArea(), 0.0);
    EXPECT_GT(hexagon.calculateArea(), 0.0);
    
    EXPECT_EQ(rhombus.getVertices().size(), 4);
    EXPECT_EQ(pentagon.getVertices().size(), 5);
    EXPECT_EQ(hexagon.getVertices().size(), 6);
}

TEST(test_59, ArrayWithFigurePointersAndDirect) {
    Array<Figure<double>*> polyArray;
    polyArray.push_back(new Rhombus<double>(4.0, 5.0, 0.0, 0.0));
    polyArray.push_back(new Pentagon<double>(3.0, 0.0, 0.0));
    
    EXPECT_EQ(polyArray.size(), 2);
    
    Array<Rhombus<double>> directArray;
    directArray.push_back(Rhombus<double>(6.0, 8.0, 1.0, 1.0));
    directArray.push_back(Rhombus<double>(5.0, 5.0, 2.0, 2.0));
    
    EXPECT_EQ(directArray.size(), 2);
    
    for (size_t i = 0; i < polyArray.size(); ++i) {
        delete polyArray[i];
    }
}
