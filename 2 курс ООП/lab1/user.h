#pragma once
#include "figure.h"

class User {
    Rectangle* rect;

public:
    User();
    User(double x1, double y1, double x2, double y2);
    ~User();

    void showInfo() const;
    void shift(double dx, double dy);
};