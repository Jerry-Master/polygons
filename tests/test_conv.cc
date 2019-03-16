#include "../Point.h"
#include "../ConvexPolygon.h"

#include <iostream>
#include <map>
#include <sstream>
using namespace std;

map<string, ConvexPolygon> pols;

void add_polygon(){
    string name;
    cin >> name;
    vector<Point> v;
    string line;
    getline(cin, line);
    istringstream iss(line);
    double x, y;
    while (iss >> x >> y) v.push_back(Point(x,y));
    pols[name] = v;
}

void remove(){
    string name;
    cin >> name;
    pols.erase(name);
}
// Assigns the first to the second
void assign(){
    string name1, name2;
    cin >> name1 >> name2;
    pols[name2] = pols[name1];
}
// Shows all the vertices of T in order, in the form (x1,y1) (x2,y2)  
void print(const ConvexPolygon& T){
    vector<Point> v = T.Hull();
    for (Point p : v) cout << '(' << p.X() << ',' << p.Y() << ") ";
    cout << endl;
}

void Union(){
    string name1, name2;
    cin >> name1 >> name2;
    print(pols[name1] + pols[name2]);
}

void intersection(){
    string name1, name2;
    cin >> name1 >> name2;
    print(pols[name1] * pols[name2]);
}

void bbox(){
    ConvexPolygon box;
    string name;
    while (cin >> name) box = ConvexPolygon().bbox({box, pols[name]});
    print(box);
}
// Tells if the first is inside the second
void isInside(){
    string name1, name2;
    cin >> name1 >> name2;
    bool insd = pols[name1].isInside(pols[name2]);
    if (insd) cout << "yes" << endl;
    else cout << "no" << endl;
}

void num_vert(){
    string name;
    cin >> name;
    cout << pols[name].num_vert() << endl;
}

void num_edges(){
    string name;
    cin >> name;
    cout << pols[name].num_edges() << endl;
}

void area(){
    string name;
    cin >> name;
    cout << pols[name].area() << endl;
}

void isRegular(){
    string name;
    cin >> name;
    cout << (pols[name].isRegular() ? "yes" : "no") << endl;
}

void centroid(){
    string name;
    cin >> name;
    Point centroid = pols[name].centroid();
    cout << '(' <<centroid.X() << ',' << centroid.Y() << ')' << endl;
}

void Hull(){
    string name;
    cin >> name;
    print(pols[name]);
}

int main(){
    cout.setf(ios::fixed);
    cout.precision(2);

    string inst;
    while (cin >> inst){
        if (inst == "polygon") add_polygon();
        else if (inst == "remove") remove();
        else if (inst == "assign") assign();

        else if (inst == "+") Union();
        else if (inst == "*") intersection();

        else if (inst == "bbox") bbox();
        else if (inst == "isInside") isInside();

        else if (inst == "num_vert") num_vert();
        else if (inst == "num_edges") num_edges();
        else if (inst == "area") area();
        else if (inst == "isRegular") isRegular();
        else if (inst == "centroid") centroid();
        else if (inst == "Hull") Hull();
    }
}
