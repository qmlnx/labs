#include "user.h"

User::User() {
    rect = new Rectangle();
}

User::User(double x1, double y1, double x2, double y2) {
    rect = new Rectangle(x1, y1, x2, y2);
}

User::~User() {
    delete rect;
}

void User::showInfo() const {
    std::cout << "Вершины: " << *rect << std::endl;
    std::cout << "Периметр: " << rect->perimeter() << std::endl;
    std::cout << "Площадь: " << rect->area() << std::endl;
}

void User::shift(double dx, double dy) {
    rect->move(dx, dy);
}