#include <bits/stdc++.h>
using namespace std;

#define sep ' '
#define endl '\n'
#define tab '\t'
#define all(x)          (x).begin(),(x).end()
const string MAP_PATH = "map.txt";
const char CSV_DELIMITER = ',';
const string WALL1 = "B";
const string WALL2 = "P";
const string DOOR = "D";
const string HIDE_KEY = "K";
const string HIDE_POWER2 = "L";
const string HIDE_POWER4 = "S";
const string AGENT = "A";
const string H_ENEMY = "H";
const string V_ENEMY = "V";
const string V_ENEMYDOWN = "VD";
const string V_ENEMYUP = "VU";
const string H_ENEMYLEFT = "HL";
const string H_ENEMYRIGHT = "HR";
const string EMPTY = "-";

typedef vector < vector < string >>    VVS;

VVS read_record(string fname) {
    VVS content;
    vector < string > row;
    string line, word;
    srand(time(0));
    fstream file(fname, ios::in);
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, CSV_DELIMITER)){
                if(word == V_ENEMY){
                    if(rand()%2==0){word=V_ENEMYUP;}
                    else{word=V_ENEMYDOWN;}
                }
                if(word == H_ENEMY){
                    if(rand()%2==0){word=H_ENEMYLEFT;}
                    else{word=H_ENEMYRIGHT;}
                }
                row.push_back(word);
            }
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
    void set_map(VVS map1){map = map1;}
    void update_enemy();
private:
    VVS map;
    int game_time;
};

class Agent{
public:
    Agent();
    void init_agent();
    pair<int,int> get_pos(){return pos;}
    void set_pos(pair<int,int> pos1){pos = pos1;}
    void make_move(string command, VVS map);
private:
    pair<int , int> pos;
};

void Agent::init_agent(){
    pos = make_pair(2,1);
}
Agent::Agent(){
    init_agent();
}
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
void show_map(VVS map, pair<int,int> pos){
    for(int i=0;i<map.size();i++){
        for (int j=0;j<map[i].size();j++){
            if (i==pos.first && j==pos.second){
                cout<<AGENT<<CSV_DELIMITER;
            }
            else{
                cout<<map[i][j]<<CSV_DELIMITER;
            }
        }
        cout<<endl;
    }
}
void Map::init_map(){
    map = read_record(MAP_PATH);
    game_time = read_game_time(MAP_PATH);
    map = init_keys_power(map);
}
void Map::update_enemy(){
    VVS map1;
    for (int i=0;i<map.size();i++){
        vector<string>row;
        for(int j=0;j<map[i].size();j++){
            row.push_back(EMPTY);
        }
        map1.push_back(row);
    }
    for(int i = 0;i<map.size();i++){
        for (int j=0;j<map[i].size();j++){
            if (map[i][j]== V_ENEMYUP && map[i-1][j]==EMPTY)map1[i-1][j] = map[i][j];
            else if (map[i][j]== V_ENEMYUP && map[i-1][j]!=EMPTY){
                map[i][j] = V_ENEMYDOWN;
                map1[i+1][j] = map[i][j];
            }
            else if (map[i][j]== V_ENEMYDOWN && map[i+1][j]==EMPTY)map1[i+1][j] = map[i][j];
            else if (map[i][j]== V_ENEMYDOWN && map[i+1][j]!=EMPTY){
                map[i][j] = V_ENEMYUP;
                map1[i-1][j] = map[i][j];
            }
            else if (map[i][j]== H_ENEMYLEFT && map[i][j-1]==EMPTY)map1[i][j-1] = map[i][j];
            else if (map[i][j] == H_ENEMYLEFT && map[i][j-1]!=EMPTY){
                map[i][j] = H_ENEMYRIGHT;
                map1[i][j+1] = map[i][j];
            }
            else if (map[i][j]== H_ENEMYRIGHT && map[i][j+1]==EMPTY)map1[i][j+1] = map[i][j];
            else if (map[i][j] == H_ENEMYRIGHT && map[i][j+1]!=EMPTY){
                map[i][j] = H_ENEMYLEFT;
                map1[i][j-1] = map[i][j];
            }
            if(map[i][j]!=EMPTY && map[i][j]!= H_ENEMYRIGHT && map[i][j]!= H_ENEMYLEFT && map[i][j]!= V_ENEMYDOWN && map[i][j]!= V_ENEMYUP)map1[i][j]=map[i][j];
        }
    }
    map = map1;
}
void Agent::make_move(string command, VVS map){
    if (command == "w" && map[pos.first-1][pos.second]!= DOOR && map[pos.first-1][pos.second]!=HIDE_POWER2 && map[pos.first-1][pos.second]!=HIDE_POWER4 &&map[pos.first-1][pos.second]!=HIDE_KEY && map[pos.first-1][pos.second]!= WALL2){
        pos = make_pair(pos.first-1,pos.second);
    }
    if (command == "s" && map[pos.first+1][pos.second]!= DOOR && map[pos.first+1][pos.second]!=HIDE_POWER2 && map[pos.first+1][pos.second]!=HIDE_POWER4 &&map[pos.first+1][pos.second]!=HIDE_KEY && map[pos.first+1][pos.second]!= WALL2){
        pos = make_pair(pos.first+1,pos.second);
    }
    if (command == "a" && map[pos.first][pos.second-1]!= DOOR && map[pos.first][pos.second-1]!=HIDE_POWER2 && map[pos.first][pos.second-1]!=HIDE_POWER4 &&map[pos.first][pos.second-1]!=HIDE_KEY && map[pos.first][pos.second-1]!=WALL2){
        pos = make_pair(pos.first, pos.second-1);
    }
    if (command == "d" &&map[pos.first][pos.second+1]!= DOOR && map[pos.first][pos.second+1]!=HIDE_POWER2 && map[pos.first][pos.second+1]!=HIDE_POWER4 &&map[pos.first][pos.second+1]!=HIDE_KEY && map[pos.first][pos.second+1]!=WALL2){
        pos = make_pair(pos.first, pos.second+1);
    }
}
class Game{
public:
    Game();
    void init_game();
    VVS get_map(){return board.get_map();}
    pair<int,int> get_agent_pos(){return agent.get_pos();}
    void turn();

private:
    Map board;
    Agent agent;
    int end_game;
};
Game::Game(){
    init_game();
}

void Game::init_game(){
    end_game = 0;
    cout<<"game start"<<endl;
}
void Game::turn(){
    time_t start;
    start=time(0);
    while(1)
    {

        string input;
        cout<<"get command";
        cin>>input;
        agent.make_move(input, board.get_map());
        if(time(0)-start>=1)
        {
            board.update_enemy();
            cout<<"-------------------------"<<endl;
            show_map(board.get_map(), agent.get_pos());
            start=start+1;
        }
    }

}
int main(){
    Game game;
    show_map(game.get_map(),game.get_agent_pos());
    game.turn();
    return 0;
}
