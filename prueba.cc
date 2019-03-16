#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

std::vector<int> genera(){
    std::vector<int> v = {100,2,3,2,1,3,4,4,2,1,2,4,43,2,12,34,3,5323,235,35};
    return v;
}

void print(const std::vector<int>& v){
    int i = 0;
    for (int p : v) {
        std::cout << p << ' ';
        i++;
        if (i == 2) return;
    }
    std::cout << std::endl;
}

bool comp (int a, int b){
    return a < b;
}

std::vector<int> nothing(std::vector<int>& v){
    v.pop_back();
    return v;
}

/**
    std::vector<int> v = genera();
    std::vector<int> b = nothing(v);
    print(b);
    std::sort(++v.begin(), v.end(), comp);
    print(v);
    ifstream f("prueba.txt");
    string line;
    getline(f, line);
    cout << line << endl;
*/

bool wrong_format(const string& file, bool image = false){
    int last = file.size()-1;
    if (last < 3) return false;
    string tail = file.substr(last-3, 4);
    cout << tail << endl;
    if (image) return (tail != ".png");
    return (tail == ".txt" or tail == ".inp" or tail == ".dat");
}

int main(){
    double x, y;
    if (cin >> x >> y) cout << "good" << endl;
    else cout << "bad" << endl;
}
