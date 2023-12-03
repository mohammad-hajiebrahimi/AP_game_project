#include <bits/stdc++.h>
using namespace std;

#define sep ' '
#define endl '\n'
#define tab '\t'
#define all(x)          (x).begin(),(x).end()
const string MAP_PATH = "map.txt";
const char CSV_DELIMITER = ',';
const string WALL1 = "B";
const string HIDE_KEY = "K";
const string HIDE_POWER2 = "L";
const string HIDE_POWER4 = "S";

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
    void init_map();
    int get_game_time(){return game_time;}
    VVS get_map(){return map;}
private:
    VVS map;
    int game_time;
};

Map::Map(){
    init_map();
}
VVS init_keys_power(VVS map){
    vector<pair<int, int>> wall_count;
    for (int i = 0 ;i<map.size();i++){
        for(int j = 0 ; j<map[i].size();j++){
            if (map[i][j] == WALL1){
                wall_count.push_back(make_pair(i,j));
            }
        }
    }
    srand(time(0));
    vector <int> random_nums;
    while (random_nums.size()!= wall_count.size()){
        int num  = rand()%wall_count.size();
        if (find(all(random_nums), num) == random_nums.end()){
            random_nums.push_back(num);
        }
    }
    for(int i=0;i<3;i++){
        map[wall_count[random_nums[i]].first][wall_count[random_nums[i]].second] = HIDE_KEY;
    }
    for (int i = 3;i<3+int((wall_count.size()-3)/2);i++){
        map[wall_count[random_nums[i]].first][wall_count[random_nums[i]].second] = HIDE_POWER2;
    }
    for (int i = 3+int((wall_count.size()-3)/2);i<wall_count.size();i++){
        map[wall_count[random_nums[i]].first][wall_count[random_nums[i]].second] = HIDE_POWER4;
    }
    return map;
}
void show_map(VVS map){
    for(int i=0;i<map.size();i++){
        for (int j=0;j<map[i].size();j++){
            cout<<map[i][j]<<CSV_DELIMITER;
        }
        cout<<endl;
    }
}
void Map::init_map(){
    map = read_record(MAP_PATH);
    game_time = read_game_time(MAP_PATH);
    map = init_keys_power(map);
    show_map(map);
}
int main(){
    Map board;
    //cout<<board.get_game_time();
    return 0;
}
