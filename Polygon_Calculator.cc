#include "Point.h"
#include "ConvexPolygon.h"

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <pngwriter.h>
#include <string>
#include <algorithm>
using namespace std;

using segment = vector<Point>;

map<string, ConvexPolygon> pols; // Polygons 
istringstream iss; // Output channel
int WIDTH = 500;
int HEIGHT = 500;

// Tells if s is included in pols
bool included (const string& s){
    return not (pols.find(s) == pols.end());
}

void error(int type){
    cout << "error: ";
    if (type == 0) cout << "command with wrong number or type of arguments";
    else if (type == 1) cout << "undefined identifier";
    else if (type == 2) cout << "not enough parameters";
    else if (type == 3) cout << "unrecognized command";
    else if (type == 4) cout << "wrong format";
    cout << endl;
}

void warning(int type){
    cout << "warning:";
    if (type == 0) cout << "not enough parameters";
    else if (type == 1) cout << "nothing to do or show";
    cout << endl;
}

void add_polygon(bool meissage = true){
    string name;
    if (not (iss >> name)) {error(0); return;}
    // Add the points
    vector<Point> hull;
    double x, y;
    while (iss >> x) {
        if (not (iss >> y)){error(2); return;}
        hull.push_back(Point(x,y));
    }
    pols[name] = hull;
    if (meissage) cout << "ok" << endl;
}
// Shows all the vertices of T in order, in the form x1 y1 x2 y2  
void print(const string& name){
    if (not included(name)) {error(1); return;}
    cout << name;
    for (Point p : pols[name].Hull() ) cout << ' ' << p.X() << ' ' << p.Y();
    cout << endl;
}
void print(){
    string name;
    if (not (iss >> name)) {error(0); return;}
    print(name);
}

// If it receives three parameters: p1, p2, p3; and p1 doesn't exists it would be created
void Union(){
    string name1, name2;
    if (not (iss >> name1 >> name2)) {error(0); return;}
    string name3;
    if (iss >> name3){
        if (not included(name2) or not included(name3)) {error(1); return;}
        pols[name1] = pols[name2] + pols[name3];
    }else{
        if (not included(name1) or not included(name2)) {error(1); return;}
        pols[name1] = pols[name1] + pols[name2];
    }
    cout << "ok" << endl;
}
// If it receives three parameters: p1, p2, p3; and p1 doesn't exists it would be created
void intersection(){
    string name1, name2;
    if (not (iss >> name1 >> name2)) {error(0); return;}
    string name3;
    if (iss >> name3){
        if (not included(name2) or not included(name3)) {error(1); return;}
        pols[name1] = pols[name2] * pols[name3];
    }else{
        if (not included(name1) or not included(name2)) {error(1); return;}
        pols[name1] = pols[name1] * pols[name2];
    }
    cout << "ok" << endl;
}
// It saves the bounding box with the name given
void bbox(){
    string name_box;
    if(not(iss >> name_box)){error(0); return;}

    bool enough_arguments = false;
    string name;
    ConvexPolygon box;
    while (iss >> name) {
        enough_arguments = true;
        if (not included(name)) {error(1); return;}
        if ((int)box.Hull().size() == 0) box = pols[name];
        else box = ConvexPolygon().bbox({box, pols[name]});
    }
    if (not enough_arguments) {error(2); return;}
    pols[name_box] = box;
    cout << "ok" << endl;
}
// Tells if the first is inside the second
void isInside(){
    string name1, name2;
    if (not(iss >> name1 >> name2)){error(0); return;}
    if (not included(name1) or not included(name2)) {error(1); return;}
    cout << (pols[name1].isInside(pols[name2]) ? "yes" : "no") << endl;
}

void vertices(){
    string name;
    if (not (iss >> name)){error(0); return;}
    if (not included(name)) {error(1); return;}
    cout << pols[name].num_vert() << endl;
}

void list(){
    bool first = true;
    for (auto element : pols) {
        if (first) {
            cout << element.first; 
            first = false;
        }
        else cout << ' ' << element.first;
    }
    cout << endl;
}

void area(){
    string name;
    if (not (iss >> name)) {error(0); return;}
    if (not included(name)) {error(1); return;}
    cout << pols[name].area() << endl;
}

void perimeter(){
    string name;
    if (not (iss >> name)) {error(0); return;}
    if (not included(name)) {error(1); return;}
    cout << pols[name].perimeter() << endl;
}

void centroid(){
    string name;
    if (not (iss >> name)) {error(0); return;}
    if (not included(name)) {error(1); return;}
    Point centroid = pols[name].centroid();
    cout << centroid.X() << ' ' << centroid.Y() << endl;
}

void setcol(){
    string name;
    if (not (iss >> name)) {error(0); return;}
    if (not included(name)) {error(1); return;}
    double r, g, b;
    if (not (iss >> r >> g >> b)) {error(0); return;}
    if (r > 1 or g > 1 or b > 1) {error(4); return;}
    pols[name].setcol({r,g,b});
    cout << "ok" << endl;
}
// Supported text formats are .txt, .inp, .dat, and for image just .png
bool wrong_format(const string& file, bool image = false){
    int last = file.size()-1;
    if (last < 3) return true;
    string tail = file.substr(last-3, 4);
    if (image) return (tail != ".png");
    // text formats
    return not (tail == ".txt" or tail == ".inp" or tail == ".dat");
}

void save(){
    string file;
    if (not (iss >> file)) {error(0); return;}
    if (wrong_format(file)) {error(4); return;}
    ofstream destination(file);
    string name;
    while (iss >> name){
        if (not included(name)) {error(1); destination.close(); return;}
        destination << name;
        vector<Point> hull = pols[name].Hull();
        for (Point p : hull) destination << ' ' << p.X() << ' ' << p.Y();
        destination << endl;
    }
    destination.close();
    cout << "ok" << endl;
}

void load(){
    string file;
    if (not (iss >> file)) {error(0); return;}
    if (wrong_format(file)) {error(4); return;}
    ifstream arrival(file);
    string polygon;
    while(getline(arrival, polygon)) {
		iss.clear();
        iss.str(polygon);
        add_polygon(false);
    }
    cout << "ok" << endl;
}
// Returns a vector with the points of the segment between P and Q
segment line(const Point& P, const Point& Q){
    if (P.X() > Q.X()) return line(Q,P);
    // Compute coefficients of the line
    double A = (Q.Y() - P.Y());
    double B = (P.X() - Q.X());
    double C = -(A*P.X() + B*P.Y());
    // Enclose the line between P and Q
	segment ret;
    // Special cases
	if (A == 0 and B == 0) return {Point(0,0)};
	if (A == 0) {
		for (int x = P.X(); x <= Q.X(); x++) ret.push_back(Point(x,(-C/B)));
	}else if (B == 0) {
		for (int y = min(P.Y(), Q.Y()); y <= max(P.Y(), Q.Y()); y++) ret.push_back(Point((-C/A),y));
	}else { // General case
		int this_y;
        int last_y = (-A/B)*P.X() - (C/B);
        // Traverse the points in the line
		for (int x = P.X()+1; x <= Q.X(); x++){
			this_y = (-A/B)*x - (C/B); 
            // Fill between consecutive x all the points in between the y-coordinates
            for (int yy = min(this_y, last_y); yy <= max(this_y, last_y); yy++) ret.push_back(Point(x, yy));
            last_y = this_y;
		}
        // Fill the last pixels
        for (int y = min(double(last_y), Q.Y()); y < max(double(last_y), Q.Y()); y++) ret.push_back(Point(Q.X()+1, y));
	}
	return ret;
}
// Plots the segment between A and B
void plot_line(pngwriter& image, const Point& A, const Point& B, const vector<double>& color){
    for (Point P : line(A, B)) image.plot(P.X(), P.Y(), color[0], color[1], color[2]);
}
// Rescale and center the image
void adjust(Point& P, Point new_Origin, double width_to, double height_to, double width_from, double height_from){
    // Change the origin
    P -= new_Origin;
    // Scale
    double x = P.X(); double y = P.Y();
    double factor;
    Point center;
    if (height_from > width_from) {
        factor = height_to/height_from;
        center = Point((WIDTH-1)/2 - (width_from*factor/2), 0);
    }else {
        factor = width_to/width_from;
        center = Point(0, (HEIGHT-1)/2 - (height_from*factor/2));
    }
    x *= factor; y *= factor;
    // Move two pixels above
    P = Point(x+2,y+2);
    // Center the image
    P += center;
}
void plot_point(const Point& A, pngwriter& image, const vector<double>& color){
    image.filledcircle(A.X(), A.Y(), (WIDTH+HEIGHT)/200, color[0], color[1], color[2]);
}
void plot(pngwriter& image, const vector<ConvexPolygon>& polygons){
    ConvexPolygon box = ConvexPolygon().bbox(polygons);
    // I'm taking into account that the first Point can either be the LL or the UL
    vector<Point> rectangle = box.Hull();
    double min_x = rectangle[0].X();
    double max_x = rectangle[2].X();
    double min_y = rectangle[1].Y();
    double max_y = rectangle[3].Y();

    double width_from = max_x - min_x;
    double height_from = max_y - min_y;

    vector<double> color(3);
    // Draw each polygon separately;
    for (const ConvexPolygon& T : polygons){
        color = T.getcol();
        vector<Point> hull = T.Hull();
        // Draw each line separately
        for (int i = 0; i < (int)hull.size(); i++) {
            Point A = hull[i];
            Point B;
            if (i == (int)hull.size()-1) B = hull[0]; // The polygon is closed
            else B = hull[i+1];
            adjust(A, Point(min_x, min_y), WIDTH - 3, HEIGHT - 3, width_from, height_from);
            adjust(B, Point(min_x, min_y), WIDTH - 3, HEIGHT - 3, width_from, height_from);
            plot_line(image, A, B, color);
            plot_point(A, image, color);
        }
    }
}

void draw(){
    string file;
    if (not (iss >> file)) {error(0); return;}
    if (wrong_format(file, true)) {error(4); return;}
    // PNGwriter compatibility with strings
    char file_c[(int)file.size()];
    strcpy(file_c, file.c_str());

    pngwriter image(WIDTH, HEIGHT, 1.0, file_c);
    string name;
    vector<ConvexPolygon> polygons;
    while (iss >> name){
        if (not included(name)) {
            error(1);
            image.close();
            return;
        }
        polygons.push_back(pols[name]);
    }
    plot(image, polygons);
    image.close();
    cout << "ok" << endl;
}
void frame(){
    int new_width = WIDTH; int new_height = HEIGHT;
    if (not (iss >> new_width >> new_height)) {error(0); return;}
    WIDTH = new_width; HEIGHT = new_height;
    cout << "ok" << endl;
}

void execute(const string& line){
	iss.clear();
    iss.str(line);
    string inst;
    iss >> inst;
    // Comments
    if (inst[0] == '#') cout << '#' << endl;
    // Input / Output
    else if (inst == "polygon") add_polygon();
    else if (inst == "print") print();
    else if (inst == "save") save();
    else if (inst == "load") load();
    else if (inst == "draw") draw();
    else if (inst == "frame") frame();
    // Retrieve information
    else if (inst == "area") area();
    else if (inst == "perimeter") perimeter();
    else if (inst == "vertices") vertices();
    else if (inst == "centroid") centroid();
    else if (inst == "list") list();
    else if (inst == "inside") isInside();
    // Make operations
    else if (inst == "intersection") intersection();
    else if (inst == "union") Union();
    else if (inst == "bbox") bbox();
    else if (inst == "setcol") setcol();
    
    else error(3);
}

int main(){
    cout.setf(ios::fixed);
    cout.precision(3);

    string command;
    while (getline(cin, command)) execute(command);
}
