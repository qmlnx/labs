#include "figure.h"
#include <cmath>

Rectangle::Rectangle() : count(4) {
    x = new double[count]{0, 1, 1, 0};
    y = new double[count]{0, 0, 1, 1};
}

Rectangle::Rectangle(double x1, double y1, double x2, double y2) : count(4) {
    x = new double[count]{x1, x2, x2, x1};
    y = new double[count]{y1, y1, y2, y2};
}

Rectangle::Rectangle(const Rectangle& other) : count(other.count) {
    x = new double[count];
    y = new double[count];
    for (int i = 0; i < count; i++) {
        x[i] = other.x[i];
        y[i] = other.y[i];
    }
}

Rectangle::~Rectangle() {
    delete[] x;
    delete[] y;
}

double Rectangle::width() const {
    return std::fabs(x[1] - x[0]);
}

double Rectangle::height() const {
    return std::fabs(y[2] - y[1]);
}

double Rectangle::perimeter() const {
    return 2 * (width() + height());
}

double Rectangle::area() const {
    return width() * height();
}

void Rectangle::move(double dx, double dy) {
    for (int i = 0; i < count; i++) {
        x[i] += dx;
        y[i] += dy;
    }
}

void Rectangle::print() const {
    for (int i = 0; i < count; i++)
        std::cout << "(" << x[i] << ", " << y[i] << ") ";
    std::cout << std::endl;
}

Rectangle Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        for (int i = 0; i < count; i++) {
            x[i] = other.x[i];
            y[i] = other.y[i];
        }
    }
    return *this;
}

Rectangle Rectangle::operator-() const {
    Rectangle r(*this);
    for (int i = 0; i < count; i++) {
        r.x[i] = -x[i];
        r.y[i] = -y[i];
    }
    return r;
}

Rectangle Rectangle::operator+(const Rectangle& other) const {
    double minX = std::fmin(x[0], other.x[0]);
    double minY = std::fmin(y[0], other.y[0]);
    double maxX = std::fmax(x[2], other.x[2]);
    double maxY = std::fmax(y[2], other.y[2]);
    return Rectangle(minX, minY, maxX, maxY);
}

std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
    for (int i = 0; i < r.count; i++)
        os << "(" << r.x[i] << ", " << r.y[i] << ") ";
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& r) {
    double x1, y1, x2, y2;
    is >> x1 >> y1 >> x2 >> y2;
    r = Rectangle(x1, y1, x2, y2);
    return is;
}