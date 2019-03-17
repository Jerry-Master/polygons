#ifndef _CONV
#define _CONV

#include "Point.h"
#include <vector>
#include <algorithm>
using namespace std;

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
        ConvexPolygon& operator= (const vector<Point>& T); // Check
        ConvexPolygon (const vector<Point>& T); // Check
        ConvexPolygon (); // Check
        // Changes the color
        void setcol (const vector<double> new_color);
        vector<double> getcol () const;

        // Intersection 
        // Cost: O(n log(m))
        ConvexPolygon operator* (const ConvexPolygon& T) const;
        // Union
        // Cost: O((m+n)log(m+n))
        ConvexPolygon operator+ (const ConvexPolygon& T) const; // Check

        // Smallest Bounding Box that contains the elements
        // Cost: O(n), n = total number of vertices
        ConvexPolygon bbox (const vector<ConvexPolygon>& V) const; // Check
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
        vector<Point> Hull () const; // Check

    private:
        /** 
        Internal representation:
        hull[i] is joined to hull[i+1] y hull[i-1]
        We can consider hull.size() == 0 and -1 == hull.size() - 1
        And hull[0] has the lowest x-coordinate
        */
        vector<Point> hull;
        vector<double> color = {0.0, 0.0, 0.0}; // Default is black

        //Useful methods either for constructor or other public methods
        
        // Returns the index/coordinate of the point with the minimum/maximum x/y-coordinate 
        // Cost: O(n)
        int min_x (const vector<Point>& P) const; // Check
        int min_y (const vector<Point>& P) const; // Check
        int max_x (const vector<Point>& P) const; // Check
        int max_y (const vector<Point>& P) const; // Check
        // For the Bounding Box function
        double min_x_value (const vector<Point>& P) const; // Check
        double min_y_value (const vector<Point>& P) const; // Check  
        double max_x_value (const vector<Point>& P) const; // Check
        double max_y_value (const vector<Point>& P) const; // Check
        //Cost: O(n log(n))
        vector<Point> simple_polygon (const vector<Point>& T) const; // Check
        // Cost: O(n)
        vector<Point> graham_scan (const vector<Point>& T) const; // Check
        // Cost: O(n log(n)), it is simple_polygon + graham_scan
        vector<Point> convexHull (const vector<Point>& T) const; // Check
        // Cost: O(log(n))
        bool isInside (const vector<Point>& T, int i1, int i2, const Point& P) const;
        bool isInside (const vector<Point>& T, const Point& P) const; // Check
        // Utilities for intersection
        void check_inside(vector<Point>& V, const Point& A, const Point& B) const;
        // Returns interior points of T1 in T2 and viceversa
        vector<Point> interiorPoints(const vector<Point>& T1, const vector<Point>& T2) const;
        // Necessary functions for the intersection
        vector<Point> cut_points(const Point& A, const Point& B, const vector<Point>& T) const;
        vector<Point> cut_points(const Point& A, const Point& B, const vector<Point>& T, int i, int j) const;
        vector<Point> cut_points(const vector<Point>& T1, const vector<Point>& T2) const;
};

#endif
