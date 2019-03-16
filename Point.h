#ifndef _POINT
#define _POINT
#define EPSILON 1e-12 

#include <cmath>
#include <cassert>

/**
This class provides all the useful functions to work with points. 
We can also identify them as vectors taking the origin as reference,
therefore all the useful operations with vectors are also implemented.

We can consider the cost of its functions as O(1)
*/

class Point{
    public:
        // Constructor
        Point& operator= (const Point& P);
        Point (double x = 0, double y = 0);

        // Coordinates
        double X () const;
        double Y () const;
        
        // Important values
        double quadrance() const; // Quadrance, just to avoid square roots
        double slope() const; // To the x-axis
        // (first goes the x and then the y) 1: ++, 2: -+, 3: --, 4: +-, 5: axis
        // To distinguish the different slopes
        int quadrant() const; 
        // Distance from this to P
        double distance(const Point& P) const;

        // Add, substract, cross-product, dot product, clockwise orientation
        Point& operator+= (const Point& P);
        Point operator+ (const Point& P) const;
        Point& operator-= (const Point& P);
        Point operator- (const Point& P) const;
        Point operator- () const;
        Point& operator*= (double lambda); // Multiplication by a scalar
        double operator^ (const Point& P) const; // Cross
        double operator* (const Point& P) const; // Dot
        bool operator== (const Point& P) const;
        // Taking the origin as reference
        // True: P1^P2 > 0
        // False: P1^P2 < 0
        // Prec: Neither P1 nor P2 are the origin
        bool clockwise (const Point& P1, const Point& P2) const;
        bool clockwise (const Point& P) const;

    private:
        double x, y;
};

#endif
