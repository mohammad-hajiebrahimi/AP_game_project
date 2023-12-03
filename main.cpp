#include <bits/stdc++.h>
using namespace std;

#define sep ' '
#define endl '\n'
#define tab '\t'
const string MAP_PATH = "map.txt";
const char CSV_DELIMITER = ',';
vector < vector < string >> read_record(string fname) {
    vector < vector < string >> content;
    vector < string > row;
    string line, word;
    fstream file(fname, ios::in);
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, CSV_DELIMITER))
                row.push_back(word);
            content.push_back(row);
        }
    }
    return content;
}
int main(){
    vector < vector < string >> map = read_record(MAP_PATH);
    return 0;
}
