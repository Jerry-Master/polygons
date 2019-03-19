#include "ConvexPolygon.h"
#include <iostream>
using namespace std;

static void append(vector<Point>& T1, const vector<Point>& T2){
    for (Point P : T2) T1.push_back(P);
}

ConvexPolygon& ConvexPolygon::operator= (const ConvexPolygon& T){
    if (this == &T) return *this;
    hull = T.Hull();
    return *this;
}
ConvexPolygon& ConvexPolygon::operator= (const vector<Point>& T){
    hull = convexHull(T);
    return *this;
}
ConvexPolygon::ConvexPolygon (const vector<Point>& T){
    hull = convexHull(T);
}
ConvexPolygon::ConvexPolygon (){
    hull = {};
}
void ConvexPolygon::setcol (const vector<double> new_color){
    color[0] = new_color[0]; color[1] = new_color[1]; color[2] = new_color[2];
}
vector<double> ConvexPolygon::getcol () const{
    return color;
}
// Useful information
// Cost: O(1)
int ConvexPolygon::num_vert () const{
    return (int)hull.size();
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
    int n = hull.size() - 1;
    double per = 0;
    for (int i = 0; i < n; i++) per += hull[i].distance(hull[i+1]);
    per += hull[n].distance(hull[0]);
    return per;
}
// Tells if all sides are equal, with a margin of 0.01%
static bool sideRegular (const vector<Point>& hull){
    double margin = 0.0001;
    int n = hull.size()-1;
    double last_side = hull[0].distance(hull[1]);  
    double this_side;
    // Traverse all sides comparing
    for (int i = 1; i < n; i++){
        this_side = hull[i].distance(hull[i+1]);  
        if (abs(last_side - this_side) > margin*(last_side*this_side/2)) return false;
        last_side = this_side;
    }
    // Last side
    this_side = hull[n].distance(hull[0]);
    if (abs(last_side - this_side) > margin*(last_side*this_side/2)) return false;
    // All tests succeeded
    return true;
}
// Tells if all angles are equal, with a margin of 1%
static bool angleRegular (const vector<Point>& hull){
    /** 
      Since it is convex, angles are between 0 and pi
      In this range the cosine function is inyective
      Therefore we can identify the angle with the cosine 
      And since the sides are equal we can identify cosines with dot products
    */
    double margin = 0.01;
    int n = hull.size() - 1;
    double last_angle = (hull[2] - hull[1]) * (hull[1] - hull[0]);  
    double this_angle;
    for (int i = 1; i < n - 1; i++){
        this_angle = (hull[i+2] - hull[i+1]) * (hull[i+1] - hull[i]);  
        if (abs(last_angle - this_angle) > margin*(last_angle*this_angle/2)) return false;
        last_angle = this_angle; 
    }
    // Next to last angle
    this_angle = (hull[0] - hull[n]) * (hull[n] - hull[n-1]);
    if (abs(last_angle - this_angle) > margin*(last_angle*this_angle/2)) return false;
    // Last angle
    last_angle = this_angle;
    this_angle = (hull[1] - hull[0]) * (hull[0] - hull[n]);
    if (abs(last_angle - this_angle) > margin*(last_angle*this_angle/2)) return false;
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
    for (Point P : hull) G += P;
    G *= 1/double(num_vert());
    return G;
}
// Returns the set of all vertices
vector<Point> ConvexPolygon::Hull () const{
    return hull;
}

// Beginning of min / max functions
int ConvexPolygon::min_x (const vector<Point>& P) const{
    int minimum = 0;
    for (int i = 1; i < (int)P.size(); i++){
        if (P[i].X() < P[minimum].X()) minimum = i;
    }
    return minimum;
}
int ConvexPolygon::min_y (const vector<Point>& P) const{
    int minimum = 0;
    for (int i = 1; i < (int)P.size(); i++){
        if (P[i].Y() < P[minimum].Y()) minimum = i;
    }
    return minimum;
}
int ConvexPolygon::max_x (const vector<Point>& P) const{
    int maximum = 0;
    for (int i = 1; i < (int)P.size(); i++){
        if (P[i].X() > P[maximum].X()) maximum = i;
    }
    return maximum;
}
int ConvexPolygon::max_y (const vector<Point>& P) const{
    int maximum = 0;
    for (int i = 1; i < (int)P.size(); i++){
        if (P[i].Y() > P[maximum].Y()) maximum = i;
    }
    return maximum;
}
double ConvexPolygon::min_x_value (const vector<Point>& P) const{
    if ((int)P.size() == 0) return 0;
    int minimum = 0;
    for (int i = 1; i < (int)P.size(); i++){
        if (P[i].X() < P[minimum].X()) minimum = i;
    }
    return P[minimum].X();
}
double ConvexPolygon::min_y_value (const vector<Point>& P) const{
    if ((int)P.size() == 0) return 0;
    int minimum = 0;
    for (int i = 1; i < (int)P.size(); i++){
        if (P[i].Y() < P[minimum].Y()) minimum = i;
    }
    return P[minimum].Y();
}
double ConvexPolygon::max_x_value (const vector<Point>& P) const{
    if ((int)P.size() == 0) return 0;
    int maximum = 0;
    for (int i = 1; i < (int)P.size(); i++){
        if (P[i].X() > P[maximum].X()) maximum = i;
    }
    return P[maximum].X();
}
double ConvexPolygon::max_y_value (const vector<Point>& P) const{
    if ((int)P.size() == 0) return 0;
    int maximum = 0;
    for (int i = 1; i < (int)P.size(); i++){
        if (P[i].Y() > P[maximum].Y()) maximum = i;
    }
    return P[maximum].Y();
}
// End of min / max functions

// Converts a set of polygons to a set of points
static vector<Point> to_points(const vector<ConvexPolygon>& V){
    vector<Point> result;
    for (ConvexPolygon C : V) append(result, C.Hull());
    return result;
}
ConvexPolygon ConvexPolygon::bbox (const vector<ConvexPolygon>& V) const{
    vector<Point> points = to_points(V);
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
/**

    Important Algorithms

*/

static bool angle_sorting (const Point& P1, const Point& P2){
    if (P1 == Point(0,0) and P1 != P2) return true;
    return P1.slope() < P2.slope();
}
// Changes the frame of reference of the points making the point Origin the new origin
static void move(vector<Point>& Polygon, const Point& Origin){
    for (Point& P : Polygon) P -= Origin; 
}
// Removes equal elements
// Prec: It is sorted
static void clean(vector<Point>& T){
    vector<Point> aux = {T[0]};
    for (int i = 1; i < (int)T.size(); i++){
        if (T[i] != T[i-1]) aux.push_back(T[i]);
    }
    T = aux;
}
// Returns a simple polygon (no intersections) for a given set of points
vector<Point> ConvexPolygon::simple_polygon (const vector<Point>& T) const{
    // Special cases
    if ((int)T.size() < 2) return T;
    // Initialize
    vector<Point> result = T;
    // Find starting point
    int min_X = min_x(result);
    swap(result[0], result[min_X]);
    // Sort by the angles
    Point Origin = result[0];
    move(result, Origin);
    sort(++result.begin(), result.end(), angle_sorting);
    clean(result);
    move(result, -Origin);

    return result;
}

vector<Point> ConvexPolygon::graham_scan (const vector<Point>& T) const{
    // Special cases
    if ((int)T.size() < 4) return T;
    // Initialize
    vector<Point> convexHull = {T[0]};
    // Traverse all points
    for (int i = 1; i < (int)T.size(); i++){
        int ii = convexHull.size()-1; // Index of last point added
        // Remove the internal points 
        while ((int)convexHull.size() > 1 and 
            not( (convexHull[ii]-convexHull[ii-1]).clockwise(T[i]-convexHull[ii]) )) { 
                convexHull.pop_back();
                ii = convexHull.size()-1;
            }
        // Add the next point
        convexHull.push_back(T[i]);
    }
    // Repeat one extra step to solve special case
    int ii = convexHull.size()-1; // Index of last point added
    // Remove the internal points 
    while ((int)convexHull.size() > 1 and 
        not( (convexHull[ii]-convexHull[ii-1]).clockwise(T[0]-convexHull[ii]) )) { 
            convexHull.pop_back();
            ii = convexHull.size()-1;
        }

    return convexHull;
}

vector<Point> ConvexPolygon::convexHull (const vector<Point>& T) const{
    return graham_scan(simple_polygon(T));
}
// Returns the union
ConvexPolygon ConvexPolygon::operator+ (const ConvexPolygon& T) const{
    vector<Point> aux = T.Hull();
    append(aux, hull);
    // Just create a convex polygon with all the points
    return ConvexPolygon(aux);
}
// Tells if a point is inside the triangle T[0] T[i] T[j]
static bool insd3(const vector<Point>& T, int i, int j, const Point& P){
    bool left1 = ( ( (T[i] - T[0]) ^ (P - T[i]) )>= 0 );
    bool left2 = ( ( (T[j] - T[i]) ^ (P - T[j]) )>= 0 );
    bool left3 = ( ( (T[0] - T[j]) ^ (P - T[0]) )>= 0 );
    return left1 and left2 and left3;
}
/** Tells if P is inside the portion delimited by the following polygon:
    - Start in T[0]
    - The next vertex is T[i]
    - Then we have all the vertices T[i..j]
    - And finally the side T[j]T[0]
*/
bool ConvexPolygon::isInside (const vector<Point>& T, int i, int j, const Point& P) const{
    // Base Case
    if (i == j - 1) return insd3(T, i, j, P);
    // Divide
    int mid = (j+i)/2;
    Point side = T[mid] - T[0];
    Point point = P - T[mid];
    // Conquer
    if (not side.clockwise(point)) return isInside(T, i, mid, P); // To the right
    return isInside(T, mid, j, P); // To the left
}
// Tells if P is inside T
bool ConvexPolygon::isInside (const vector<Point>& T, const Point& P) const{
    if ((int)T.size() < 3) return false;
    return isInside(T,1,(int)T.size()-1,P);
}
// Tells if this polygon is inside T
bool ConvexPolygon::isInside (const ConvexPolygon& T) const{
    vector<Point> T_hull = T.Hull();
    for (Point P : hull) if (not isInside(T_hull, P)) return false;
    return true;
}
// Returns the interior points of T1 in T2 and viceversa
vector<Point> ConvexPolygon::interiorPoints(const vector<Point>& T1, const vector<Point>& T2) const{
    vector<Point> result;
    for (Point P : T1) if (isInside(T2, P)) result.push_back(P);
    for (Point P : T2) if (isInside(T1, P)) result.push_back(P);
    return result;
}
// Returns 1 if it is to the 'right', -1 if it is to the 'left', and 0 if is inside the line AB
// By 'right' I mean in the positive sense of rotation
static int side(const Point& P, const Point& A, const Point& B){
    Point AB = B - A;
    Point AP = P - A;
    double prod = AB ^ AP;
    if (prod == 0) return 0;
    if (prod > 0) return 1;
    return -1;
}
// Return the cross point of the AB and CD
// Prec: Neither C nor D are inside AB (det = 0)
static Point cross_point (const Point& A, const Point& B, const Point& C, const Point& D){
    // Compute coefficients of the line AB: Ax + By = C1
    double Ax = (B.Y() - A.Y());
    double By = (A.X() - B.X());
    double C1 = (Ax * A.X() + By * A.Y());
    // Compute coefficients of the line CD: Cx + Dy = C1
    double Cx = (D.Y() - C.Y());
    double Dy = (C.X() - D.X());
    double C2 = (Cx * C.X() + Dy * C.Y());
    // Use Cramer's rule
    double det = Ax * Dy - By * Cx; 
    double x = (C1 * Dy -  C2 * By)/(det);
    double y = (C2 * Ax -  C1 * Cx)/(det);
    return Point(x,y);
}
// Returns the cut points of the segment AB and T, recursively.
// Invariant: If AB intersects any segment T[i]T[i+1] it must be between T[i..j]
vector<Point> ConvexPolygon::cut_points(const Point& A, const Point& B, const vector<Point>& T, int i, int j) const{
    // Precomputations
    int side_i = side(T[i], A, B);
    int side_j = side(T[j], A, B);
    // Special cases
    bool i_inside = (side_i == 0);
    bool j_inside = (side_j == 0);
    if (i_inside and j_inside) return {T[i], T[j]};
    else if (i_inside) return {T[i]};
    else if (j_inside) return {T[j]};
    // Base case
    if (i+1 == j) {
        if (side_i == side_j) return {};
        Point cross = cross_point(A, B, T[i], T[j]);
        if (cross.isInside(A, B)) return {cross};
        return {};
    }
    // Divide
    int m = (i+j)/2;
    int side_m = side(T[m], A, B);
    if (side_m == 0) return {T[m]}; // Special case
    // Conquer
    if (side_i != side_j){ 
        if (side_i != side_m) return cut_points(A, B, T, i, m);
        if (side_m != side_j) return cut_points(A, B, T, m, j);
    }else {
        // Both T[i..m] and T[m..j] intersect the line
        if (side_m != side_i) {
            vector<Point> aux = cut_points(A, B, T, i, m);
            append(aux, cut_points(A, B, T, m, j));
            return aux;
        }
        // Move the line
        Point AA = T[m];
        Point BB = (T[m] + (B-A));
        // Compare to the new line
        int side_before = side(T[m-1], AA, BB);
        int side_next = side(T[m+1], AA, BB);
        // Check which way we are getting closer, or if it imposible to do so
        if (side_before == side_next) return {};
        if (side_before != side_m) return cut_points(A, B, T, i, m);
        if (side_next != side_m) return cut_points(A, B, T, m, j);
        return {};
    }
    return {};
}
// Returns the cut points of the segment AB and T
vector<Point> ConvexPolygon::cut_points(const Point& A, const Point& B, const vector<Point>& T) const{
    int n = T.size()-1;
    // Apply recursion
    vector<Point> result = cut_points(A, B, T, 0, n);
    // Remember last side
    Point cross = cross_point(A, B, T[n], T[0]); 
    if (cross.isInside(A, B) and cross.isInside(T[n], T[0])) result.push_back(cross);
    return result;
}
// Return the cut points of T1 and T2
vector<Point> ConvexPolygon::cut_points(const vector<Point>& T1, const vector<Point>& T2) const{
    vector<Point> aux;
    int n = T1.size()-1;
    // Compute the intersections side by side
    for (int i = 0; i < n; i++) append(aux, cut_points(T1[i], T1[i+1], T2));
    append(aux, cut_points(T1[n], T1[0], T2)); // Remember last side
    return aux;
}
ConvexPolygon ConvexPolygon::operator* (const ConvexPolygon& T) const{
    // First add the intersections of the sides
    vector<Point> result = cut_points(hull, T.Hull());
    // Then add the points interior to one of the polygons
    append(result, interiorPoints(hull, T.Hull()));
    // Finally order everything
    return ConvexPolygon(result);
}


