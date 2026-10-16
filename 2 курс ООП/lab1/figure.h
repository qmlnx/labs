#pragma once
#include <iostream>

class Rectangle {
    double* x;
    double* y;
    int count;

public:
    Rectangle();
    Rectangle(double x1, double y1, double x2, double y2);
    Rectangle(const Rectangle& other);
    ~Rectangle();

    double width() const;
    double height() const;
    double perimeter() const;
    double area() const;
    void move(double dx, double dy);
    void print() const;

    Rectangle operator=(const Rectangle& other);
    Rectangle operator-() const;
    Rectangle operator+(const Rectangle& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& r);
    friend std::istream& operator>>(std::istream& is, Rectangle& r);
};