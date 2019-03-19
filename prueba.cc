#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "Point.h"
using namespace std;


int main(){
    istringstream ss;
    string line;
    getline(cin, line);
    ss.str(line);
    string auxx;
    //ss >> auxx;
    cout << ss.str() << endl;
    getline(cin, line);
    
    ss.str(line);
    
    ss >> auxx;
    cout << auxx << endl;
}
