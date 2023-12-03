#include <bits/stdc++.h>
using namespace std;

#define sep ' '
#define endl '\n'
#define tab '\t'
const string MAP_PATH = "map.txt";
const char CSV_DELIMITER = ',';
typedef vector < vector < string >>    VVS;

VVS read_record(string fname) {
    VVS content;
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
int read_game_time(string fname){
    fstream file(fname, ios::in);
    string line;
    getline(file, line);
    int game_time = stoi(line);
    return game_time;
}

class Map{
public:
    Map();
    void init_map(){
        map = read_record(MAP_PATH);
        game_time = read_game_time(MAP_PATH);
    }
    int get_game_time(){return game_time;}
    VVS get_map(){return map;}

private:
    VVS map;
    int game_time;
};

Map::Map(){
    init_map();
}
int main(){
    Map board;
    cout<<board.get_game_time();
    return 0;
}
