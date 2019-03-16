#ifndef _CONV
#define _CONV

#include "Point.h"
#include <vector>
#include <algorithm>

/**
To clarify things, in the followings n = hull.size() and m = T.size()
Or if there are two polygons T1 and T2, n = T1.size() and m = T2.size()
Or n is simply the size of the attribute to the function

The vertices are ordered counterclockwise
*/

class ConvexPolygon{
    public:
        // Constructor
        ConvexPolygon& operator= (const ConvexPolygon& T); // Check
        ConvexPolygon& operator= (const std::vector<Point>& T); // Check
        ConvexPolygon (const std::vector<Point>& T); // Check
        ConvexPolygon (); // Check
        // Changes the color
        void setcol (const std::vector<double> new_color);
        std::vector<double> getcol () const;

        /**
            Both the intersection and the union doesn't change the father polygon,
            but they return a reference to the polygon created in order to be able 
            to concatenate operations
        */

        // Intersection 
        // Cost: O(n^2)
        ConvexPolygon operator* (const ConvexPolygon& T) const;
        // Union
        // Cost: O((m+n)log(m+n))
        ConvexPolygon operator+ (const ConvexPolygon& T) const; // Check

        // Smallest Bounding Box that contains the elements
        // Cost: O(n), n = total number of vertices
        ConvexPolygon bbox (const std::vector<ConvexPolygon>& V) const; // Check?
        // Tells if this polygon is inside the polygon T
        // Cost: O(n log(m)) 
        bool isInside (const ConvexPolygon& T) const; // Check

        // Useful information
        // Cost: O(1)
        int num_vert () const; // Check
        // Cost: O(1)
        int num_edges () const; // Check
        // Cost: O(n) flops
        double area () const; // Check
        // Cost: O(n) flops
        double perimeter () const;
        // Considering the emptygon, monogon and dygon as regular
        // Cost: O(n) flops
        bool isRegular () const; // Check
        // Cost: O(n) additions
        Point centroid () const; // Check
        // Returns the set of all vertices
        std::vector<Point> Hull () const; // Check

    private:
        /** 
        Internal representation:
        hull[i] is joined to hull[i+1] y hull[i-1]
        We can consider hull.size() == 0 and -1 == hull.size() - 1
        And hull[0] has the lowest x-coordinate
        */
        std::vector<Point> hull;
        std::vector<double> color = {0.0, 0.0, 0.0}; // Default is black

        //Useful methods either for constructor or other public methods
        
        // Returns the index/coordinate of the point with the minimum/maximum x/y-coordinate 
        // Cost: O(n)
        int min_x (const std::vector<Point>& P) const; // Check
        int min_y (const std::vector<Point>& P) const; // Check
        int max_x (const std::vector<Point>& P) const; // Check
        int max_y (const std::vector<Point>& P) const; // Check
        // For the Bounding Box function
        double min_x_value (const std::vector<Point>& P) const; // Check
        double min_y_value (const std::vector<Point>& P) const; // Check  
        double max_x_value (const std::vector<Point>& P) const; // Check
        double max_y_value (const std::vector<Point>& P) const; // Check
        //Cost: O(n log(n))
        std::vector<Point> simple_polygon (const std::vector<Point>& T) const; // Check
        // Cost: O(n + m), for the union
        std::vector<Point> simple_polygon (const ConvexPolygon& T1, const ConvexPolygon& T2) const;
        // Cost: O(n)
        std::vector<Point> graham_scan (const std::vector<Point>& T) const; // Check
        // Cost: O(n log(n)), it is simple_polygon + graham_scan
        std::vector<Point> convexHull (const std::vector<Point>& T) const; // Check
        // Cost: O(log(n))
        bool isInside (const std::vector<Point>& T, const Point& P) const; // Check
        // Returns the points of this inside this, and the index of the beginning and ending in i and j
        std::vector<Point> pointsInside(const std::vector<Point>& T, int i, int j) const;
};

#endif
