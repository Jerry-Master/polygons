#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "Point.h"
using namespace std;

bool wrong_format(const string& file, bool image = false){
    int last = file.size()-1;
    if (last < 3) return false;
    string tail = file.substr(last-3, 4);
    cout << tail << endl;
    if (image) return (tail != ".png");
    return (tail == ".txt" or tail == ".inp" or tail == ".dat");
}
void check_inside(std::vector<Point>& V, const Point& A, const Point& B) {
    if (V.size() == 0) return;
    if (V.size() == 1) if (V[0].isInside(A, B)) return;
    bool a_inside = A.isInside(V[0], V[1]);
    cout << a_inside << endl;
    bool b_inside = B.isInside(V[0], V[1]);
    cout << b_inside << endl;
    if (a_inside and b_inside) V = {A, B};
    else if (a_inside) {
        if (V[0].isInside(B, V[1])) V[1] = A;
        else V[0] = A;
    }else {
        if (V[0].isInside(A, V[1])) V[1] = B;
        else V[0] = B;
    }
}

int main(){
    Point A(0.0,0.0);
    Point B(2.0,0.0);
    Point C(1.0,0.0);
    Point D(-1.0,0.0);
    cout << A.isInside(B, C) << endl;
    vector<Point> V = {A,B};
    check_inside(V, C, D);
    Point E = V[0];
    Point F = V[1];
    cout << E.X() << "," << E.Y() << endl;
    cout << F.X() << "," << F.Y() << endl;
}
