#include "Point.h"

// Constructor
Point& Point::operator= (const Point& P){
    x = P.X(); y = P.Y();
    return *this;
}
Point::Point (double x2, double y2) : x(x2), y(y2) {}

// Coordinates
double Point::X () const {
    return x;
}
double Point::Y () const {
    return y;
}

// Important values
// Quadrance, just to avoid square roots
double Point::quadrance() const {
    return x*x + y*y;
} 
// To the x-axis
double Point::slope() const {
    if (abs(x) < EPSILON) return INFINITY;
    return y/x;
}
// (first goes the x and then the y) 1: ++, 2: -+, 3: --, 4: +-, 5: axis
int Point::quadrant() const {
    if (x > 0 and y > 0) return 1;
    if (x < 0 and y > 0) return 2;
    if (x < 0 and y < 0) return 3;
    if (x > 0 and y < 0) return 4;
    // Dealing with precision issues around the axis
    if (abs(x) < EPSILON or abs(y) > EPSILON) return 5;
    else assert(false);
} 
double Point::distance(const Point& P) const{
    return sqrt((P - *this).quadrance());
}

// Add, substract, cross-product, dot product, clockwise orientation
Point& Point::operator+= (const Point& P){
    x += P.X(); y += P.Y();
    return *this;
}
Point Point::operator+ (const Point& P) const{
    Point _aux = *this;
    _aux += P;
    return _aux;
}
Point& Point::operator-= (const Point& P){
    x -= P.X(); y -= P.Y();
    return *this;
}
Point Point::operator- (const Point& P) const{
    Point _aux = *this;
    _aux -= P;
    return _aux;
}
Point Point::operator- () const{
    Point _aux(-x, -y);
    return _aux;
}
// Multiplication by a scalar
Point& Point::operator*= (double lambda){
    x *= lambda; y *= lambda;
    return *this;
}
// Cross-product
double Point::operator^ (const Point& P) const{
    return x * P.Y() - y * P.X();
}
// Dot-product
double Point::operator* (const Point& P) const{
    return x * P.X() + y * P.Y();
}
bool Point::operator== (const Point& P) const{
    return x == P.X() and y == P.Y();
}
bool Point::clockwise (const Point& P1, const Point& P2) const{
    return (P1 ^ P2) >= 0;
}
bool Point::clockwise (const Point& P) const{
    return clockwise(*this, P) > 0;
}
