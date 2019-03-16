#include "ConvexPolygon.h"
#include <iostream>
// std::cout << "a1: " << this_angle << ", " << "a2: " << last_angle << std::endl;

ConvexPolygon& ConvexPolygon::operator= (const ConvexPolygon& T){
    if (this == &T) return *this;
    hull = T.Hull();
    return *this;
}
ConvexPolygon& ConvexPolygon::operator= (const std::vector<Point>& T){
    hull = convexHull(T);
    return *this;
}
ConvexPolygon::ConvexPolygon (const std::vector<Point>& T){
    hull = convexHull(T);
}
ConvexPolygon::ConvexPolygon (){
    hull = {};
}
void ConvexPolygon::setcol (const std::vector<double> new_color){
    color[0] = new_color[0]; color[1] = new_color[1]; color[2] = new_color[2];
}
std::vector<double> ConvexPolygon::getcol () const{
    return color;
}
// Useful information
// Cost: O(1)
int ConvexPolygon::num_vert () const{
    return hull.size();
}
// Cost: O(1)
int ConvexPolygon::num_edges () const{
    if (num_vert() >= 3) return num_vert();
    if (num_vert() == 2) return 1;
    return 0;
}
// Returns the area of a triangle
static double triangle_area(const Point& A, const Point& B, const Point& C){
    return abs(((B - A) ^ (C - A))/2);
}
// Returns the area of this polygon
double ConvexPolygon::area () const{
    double area = 0;
    for (int i = 1; i < num_vert()-1; i++){
        area += triangle_area(hull[0], hull[i], hull[i+1]);
    }
    return area;
}
double ConvexPolygon::perimeter () const{
    // Special cases
    if (num_vert() < 2) return 0;
    if (num_vert() == 2) return hull[0].distance(hull[1]);
    // Add each side
    double per = 0;
    for (int i = 0; i < hull.size()-1; i++) per += hull[i].distance(hull[i+1]);
    per += hull[hull.size()-1].distance(hull[0]);
    return per;
}
// Tells if all sides are equal, with a margin of 0.01%
static bool sideRegular (const std::vector<Point>& hull){
    double last_side = hull[0].distance(hull[1]);  
    double this_side;
    for (int i = 1; i < hull.size()-1; i++){
        this_side = hull[i].distance(hull[i+1]);  
        if (abs(last_side - this_side) > 0.0001*(last_side*this_side/2)) return false;
        last_side = this_side;
    }
    this_side = hull[hull.size()-1].distance(hull[0]);
    if (abs(last_side - this_side) > 0.0001*(last_side*this_side/2)) return false;
    // All tests succeeded
    return true;
}
// Tells if all angles are equal, with a margin of 1%
static bool angleRegular (const std::vector<Point>& hull){
    // Since it is convex, angles are between 0 and pi
    // In this range the cosine function is inyective
    // Therefore we can identify the angle with the cosine 
    // And since the sides are equal we can identify cosines with dot products
    double last_angle = (hull[2] - hull[1]) * (hull[1] - hull[0]);  
    double this_angle;
    for (int i = 1; i < hull.size()-2; i++){
        this_angle = (hull[i+2] - hull[i+1]) * (hull[i+1] - hull[i]);  
        if (abs(last_angle - this_angle) > 0.01*(last_angle*this_angle/2)) return false;
        last_angle = this_angle;
    }
    int i = hull.size() - 1;
    // Last two angles
    this_angle = (hull[0] - hull[i]) * (hull[i] - hull[i-1]);
    if (abs(last_angle - this_angle) > 0.01*(last_angle*this_angle/2)) return false;
    last_angle = this_angle;
    this_angle = (hull[1] - hull[0]) * (hull[0] - hull[i]);
    if (abs(last_angle - this_angle) > 0.01*(last_angle*this_angle/2)) return false;
    // All tests succedded
    return true;
}
// Tells if this polygon is regular
bool ConvexPolygon::isRegular () const{
    // Special cases
    if (num_vert() < 3) return true;
    return sideRegular(hull) and angleRegular(hull);
}
// Returns the centroid as a point
Point ConvexPolygon::centroid () const{
    Point G(0,0);
    for (Point p : hull) G += p;
    double n = hull.size();
    G *= 1/n;
    return G;
}
// Returns the set of all vertices
std::vector<Point> ConvexPolygon::Hull () const{
    return hull;
}

// Beginning of min / max functions
int ConvexPolygon::min_x (const std::vector<Point>& P) const{
    int minimum = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].X() < P[minimum].X()) minimum = i;
    }
    return minimum;
}
int ConvexPolygon::min_y (const std::vector<Point>& P) const{
    int minimum = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].Y() < P[minimum].Y()) minimum = i;
    }
    return minimum;
}
int ConvexPolygon::max_x (const std::vector<Point>& P) const{
    int maximum = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].X() > P[maximum].X()) maximum = i;
    }
    return maximum;
}
int ConvexPolygon::max_y (const std::vector<Point>& P) const{
    int maximum = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].Y() > P[maximum].Y()) maximum = i;
    }
    return maximum;
}
double ConvexPolygon::min_x_value (const std::vector<Point>& P) const{
    if (P.size() == 0) return 0;
    int minimum = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].X() < P[minimum].X()) minimum = i;
    }
    return P[minimum].X();
}
double ConvexPolygon::min_y_value (const std::vector<Point>& P) const{
    if (P.size() == 0) return 0;
    int minimum = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].Y() < P[minimum].Y()) minimum = i;
    }
    return P[minimum].Y();
}
double ConvexPolygon::max_x_value (const std::vector<Point>& P) const{
    if (P.size() == 0) return 0;
    int maximum = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].X() > P[maximum].X()) maximum = i;
    }
    return P[maximum].X();
}
double ConvexPolygon::max_y_value (const std::vector<Point>& P) const{
    if (P.size() == 0) return 0;
    int maximum = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].Y() > P[maximum].Y()) maximum = i;
    }
    return P[maximum].Y();
}
// End of min / max functions

/**

    Important Algorithms

*/

static bool angle_sorting (const Point& P1, const Point& P2){
    return P1.slope() < P2.slope();
}
// Changes the frame of reference of the points making the point Origin the new origin
static void move(std::vector<Point>& Polygon, const Point& Origin){
    for (Point& P : Polygon) P -= Origin; 
}
/**static void print(const std::vector<Point>& T){
    for (Point p : T) std::cout << p.X() << "," << p.Y() << " ";
    std::cout << std::endl;
}*/

// Returns a simple polygon (no intersections) for a given set of points
std::vector<Point> ConvexPolygon::simple_polygon (const std::vector<Point>& T) const{
    // Special cases
    if (T.size() < 2) return T;
    // Initialize
    std::vector<Point> Copy = T;
    // Find starting point
    int min_X = min_x(Copy);
    std::swap(Copy[0], Copy[min_X]);
    // Sort by the angles
    Point aux = Copy[0];
    move(Copy, aux);
    std::sort(++Copy.begin(), Copy.end(), angle_sorting);
    move(Copy, -aux);

    return Copy;
}

std::vector<Point> ConvexPolygon::graham_scan (const std::vector<Point>& T) const{
    // Special cases
    if (T.size() < 4) return T;
    // Initialize
    std::vector<Point> convexHull = {T[0]};
    // Traverse all points
    for (int i = 1; i < T.size(); i++){
        int ii = convexHull.size()-1; // Index of last point added
        // Remove the internal points 
        while (convexHull.size() > 1 and 
            not(Point().clockwise(convexHull[ii]-convexHull[ii-1], // Side 1
            T[i]-convexHull[ii]))) { // Side 2
                convexHull.pop_back();
                ii = convexHull.size()-1;
            }
        // Add the next point
        convexHull.push_back(T[i]);
    }
    return convexHull;
}

std::vector<Point> ConvexPolygon::convexHull (const std::vector<Point>& T) const{
    return graham_scan(simple_polygon(T));
}
static void append(std::vector<Point>& T1, const std::vector<Point>& T2){
    for (Point P : T2) T1.push_back(P);
}
// Returns segment that intersects AB if it exists
// Invariant: This segment is for sure between T[i..j]
static std::vector<Point> cut_points(const Point& A, const Point& B, const ConvexPolygon& T, int i, int j){
    return {A, B};
}
// Modifies V to contain the points that are inside the segment AB, both inclusive
static void check_inside(std::vector<Point>& V, const Point& A, const Point& B){

}
// Returns the cut points of the segment AB and T, if A or B are inside T they are returned as well
static std::vector<Point> cut_points(const Point& A, const Point& B, const ConvexPolygon& T){
    int m = (T.num_vert()-1)/2;
    std::vector<Point> result = cut_points(A, B, T, 0, m);
    append(result, cut_points(A, B, T, m, T.num_vert()-1));
    check_inside(result, A, B);
    return result;
}
ConvexPolygon ConvexPolygon::operator* (const ConvexPolygon& T) const{return ConvexPolygon();
    std::vector<Point> result;
    for (int i = 0; i < hull.size()-1; i++){
        append(result, cut_points(hull[i], hull[i+1], T));
    }
    append(result, cut_points(hull[hull.size()-1], hull[0], T));
    return ConvexPolygon(result);
}
ConvexPolygon ConvexPolygon::operator+ (const ConvexPolygon& T) const{
    std::vector<Point> Copy = T.Hull();
    append(Copy, hull);
    // Just create a convex polygon with all the points
    return ConvexPolygon(Copy);
}
static std::vector<Point> to_points(const std::vector<ConvexPolygon>& V){
    std::vector<Point> result;
    for (ConvexPolygon C : V) append(result, C.Hull());
    return result;
}
ConvexPolygon ConvexPolygon::bbox (const std::vector<ConvexPolygon>& V) const{
    std::vector<Point> points = to_points(V);
    double x_min = min_x_value(points);
    double y_min = min_y_value(points);
    double x_max = max_x_value(points);
    double y_max = max_y_value(points);

    Point LL(x_min, y_min);
    Point LR(x_max, y_min); 
    Point UR(x_max, y_max);
    Point UL(x_min, y_max);
    return ConvexPolygon({LL, LR, UR, UL});
}
bool ConvexPolygon::isInside (const ConvexPolygon& T) const{
    std::vector<Point> T_hull = T.Hull();
    for (Point P : hull) if (not isInside(T_hull, P)) return false;
    return true;
}
// Tells if a point is inside the triangle T[0] T[i1] T[i2]
static bool insd3(const std::vector<Point>& T, int i1, int i2, const Point& P){
    bool left1 = (T[i1] - T[0]).clockwise(P - T[i1]);
    bool left2 = (T[i2] - T[i1]).clockwise(P - T[i2]);
    bool left3 = (T[0] - T[i2]).clockwise(P - T[0]);
    return left1 and left2 and left3;
}
/** Tells if P is inside the portion delimited by the following polygon:
    - Start in T[0]
    - The next vertex is T[i1]
    - Then we have all the vertices T[i1..i2]
    - And finally the side T[i2]T[0]
*/
static bool isInterior (const std::vector<Point>& T, int i1, int i2, const Point& P){
    // Base Case
    if (i1 == i2 - 1) return insd3(T, i1, i2, P);
    // Divide
    int mid = (i2+i1)/2;
    Point side = T[mid] - T[0];
    Point point = P - T[mid];
    // Conquer
    if (not side.clockwise(point)) return isInterior(T, i1, mid, P); // To the right
    return isInterior(T, mid, i2, P); // To the left
}
bool ConvexPolygon::isInside (const std::vector<Point>& T, const Point& P) const{
    if (T.size() < 3) return false;
    return isInterior(T,1,T.size()-1,P);
}
