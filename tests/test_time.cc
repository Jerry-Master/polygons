#include "../Point.h"
#include "../ConvexPolygon.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <cmath>
using namespace std;

// Returns the actual time in seconds
double this_time(){
    return clock()/double(CLOCKS_PER_SEC);
}
// Prints the time it takes to construct a polygon from N points
void time_constructor(int N){
    vector<Point> T;
    for (int i = 0; i < N; i++){
        Point P(rand(), rand());
        T.push_back(P);
    }
    double t1 = this_time();
    ConvexPolygon some_polygon = T;
    double t2 = this_time();
    
    cout << "For N = " << N << ", the constructor took " << t2 - t1 << " seconds." << endl;
}
// Generates random points in a circle with random center
vector<Point> random_circle(int N){
    vector<Point> T1;
    Point center(rand(), rand());
    for (int i = 0; i < N; i++){
        Point P(rand(), rand());
        double modul = sqrt(P.quadrance());
        double scale = 1000000/modul;
        P *= scale;
        P -= center;
        T1.push_back(P);
    }
    return T1;
}
// Prints the time it takes to intersect two polygons of size N and M points
void time_intersection(int N){
    ConvexPolygon P1 = random_circle(N);
    ConvexPolygon P2 = random_circle(N);
    ConvexPolygon P3;

    double t1 = this_time();
    P3 = P1 * P2;
    double t2 = this_time();
    
    cout << "For N = " << P1.Hull().size() << " and M = " << P2.Hull().size() << ", the intersection took " << t2 - t1 << " seconds." << endl;
}
// Prints the time it takes to do the union of two polygons of size N and M points
void time_union(int N){
    ConvexPolygon P1 = random_circle(N);
    ConvexPolygon P2 = random_circle(N);
    ConvexPolygon P3;

    double t1 = this_time();
    P3 = P1 + P2;
    double t2 = this_time();
    
    cout << "For N = " << P1.Hull().size() << " and M = " << P2.Hull().size() << ", the union took " << t2 - t1 << " seconds." << endl;
}
// Prints the time it takes to check if two polygons of size N and M points are one inside the other
void time_interior(int N){
    ConvexPolygon P1 = random_circle(N);
    ConvexPolygon P2 = random_circle(N);
    bool insd;

    double t1 = this_time();
    insd = P1.isInside(P2);
    double t2 = this_time();
    
    cout << "For N = " << P1.Hull().size() << " and M = " << P2.Hull().size() << ", the isInside function took " << t2 - t1 << " seconds." << endl;
}
// Check the time the constructor, intersection, union and isInside functions take
void check_time(int N){
    time_constructor(N);
    time_intersection(N);
    time_union(N);
    time_interior(N);
}

int main(){
    srand(time(NULL)); // Initialize at random (almost)
    for (int N = 10; N <= 1e6; N *= 10) check_time(N);
}