#include "../Point.h"

#include <iostream>
#include <map>
using namespace std;

map<string, Point> dots;

void add_point(){
    string name;
    double x, y;
    cin >> name >> x >> y;
    dots[name] = Point(x,y);
}

void remove(){
    string name;
    cin >> name;
    dots.erase(name);
}
// Assigns the first to the second
void assign(){
    string name1, name2;
    cin >> name1 >> name2;
    dots[name2] = dots[name1];
}

void add_cum(){
    string name1, name2;
    cin >> name1 >> name2;
    dots[name1] += dots[name2];
}

void add(){
    string name1, name2;
    cin >> name1 >> name2;
    Point aux = dots[name1] + dots[name2];
    cout << aux.X() << ' ' << aux.Y() << endl;
}

void substract_cum(){
    string name1, name2;
    cin >> name1 >> name2;
    dots[name1] -= dots[name2];
}

void substract(){
    string name1, name2;
    cin >> name1 >> name2;
    Point aux = dots[name1] - dots[name2];
    cout << aux.X() << ' ' << aux.Y() << endl;
}

void scalar(){
    string name;
    double lambda;
    cin >> name >> lambda;
    dots[name] *= lambda;
    cout << dots[name].X() << " " << dots[name].Y() << endl;
}

void cross(){
    string name1, name2;
    cin >> name1 >> name2;
    double aux = dots[name1] ^ dots[name2];
    cout << aux << endl;
}

void dot(){
    string name1, name2;
    cin >> name1 >> name2;
    double aux = dots[name1] * dots[name2];
    cout << aux << endl;
}

void equal(){
    string name1, name2;
    cin >> name1 >> name2;
    cout << (dots[name1] == dots[name2] ? "yes" : "no") << endl;
}

void clockwise(){
    string name1, name2;
    cin >> name1 >> name2;
    cout << (dots[name1].clockwise(dots[name2]) ? "yes" : "no") << endl;
}

void ics(){
    string name;
    cin >> name;
    cout << dots[name].X() << endl;
}

void greek_y(){
    string name;
    cin >> name;
    cout << dots[name].Y() << endl;
}

void quad(){
    string name;
    cin >> name;
    cout << dots[name].quadrance() << endl;
}

void slope(){
    string name;
    cin >> name;
    cout << dots[name].slope() << endl;
}

void quadrant(){
    string name;
    cin >> name;
    cout << dots[name].quadrant() << endl;
}

void distance(){
    string name1, name2;
    cin >> name1 >> name2;
    cout << dots[name1].distance(dots[name2]) << endl;
}

int main(){
    cout.setf(ios::fixed);
    cout.precision(2);

    string inst;
    while (cin >> inst){
        if (inst == "add_point") add_point();
        if (inst == "remove") remove();
        if (inst == "assign") assign();

        if (inst == "+=") add_cum();
        if (inst == "+") add();
        if (inst == "-=") substract_cum();
        if (inst == "-") substract();
        if (inst == "*=") scalar();
        if (inst == "^") cross();
        if (inst == "*") dot();
        if (inst == "==") equal();

        if (inst == "clockwise") clockwise();

        if (inst == "X") ics();
        if (inst == "Y") greek_y();

        if (inst == "quad") quad();
        if (inst == "slope") slope();
        if (inst == "quadrant") quadrant();
        if (inst == "distance") distance();
    }
}
