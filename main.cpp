#include <bits/stdc++.h>

#include <stdio.h>

#include <sys/ioctl.h>

#include <termios.h>

#include <stdbool.h>

#include <unistd.h>

#include <SFML/Graphics.hpp>

#include <SFML/Window.hpp>

#include <SFML/System.hpp>

using namespace std;

#define sep ' '
#define delimiter ',,,'
#define endl '\n'
#define tab '\t'
#define all(x)(x).begin(), (x).end()
const string MAP_PATH = "map.txt";
const char CSV_DELIMITER = ',';
const string WALL1 = "B";
const string WALL2 = "P";
const string DOOR = "D";
const string HIDE_KEY = "K";
const string HIDE_POWER2 = "L";
const string HIDE_POWER3 = "S";
const string SHOW_DOOR = "d";
const string SHOW_KEY = "k";
const string SHOW_POWER2 = "l";
const string SHOW_POWER3 = "s";
const string AGENT = "A";
const string H_ENEMY = "H";
const string V_ENEMY = "V";
const string V_ENEMYDOWN = "VD";
const string V_ENEMYUP = "VU";
const string H_ENEMYLEFT = "HL";
const string H_ENEMYRIGHT = "HR";
const string EMPTY = "-";
const string BOMB = "T";
const string GRASS_IMAGE = "Pic/grass.png";
const string WALL1_IMAGE = "Pic/wall-1.png";
const string WALL2_IMAGE = "Pic/wall-2.png";
const string V_ENEMYUP_IMAGE = "Pic/up-enemy.png";
const string V_ENEMYDOWN_IMAGE = "Pic/down-enemy.png";
const string H_ENEMYLEFT_IMAGE = "Pic/left-enemy.png";
const string H_ENEMYRIGHT_IMAGE = "Pic/right-enemy.png";
const string KEY_IMAGE = "Pic/key.png";
const string POWER2_IMAGE = "Pic/powerup2.jpeg";
const string POWER3_IMAGE = "Pic/powerup3.jpeg";
const string DOOR_IMAGE = "Pic/door.jpeg";
const string BOMB_IMAGE = "Pic/bomb.png";
const string AGENT_UP_IMAGE = "Pic/up.png";
const string AGENT_DOWN_IMAGE = "Pic/down.png";
const string AGENT_LEFT_IMAGE = "Pic/left.png";
const string AGENT_RIGHT_IMAGE = "Pic/right.png";
typedef vector < vector < string >> VVS;

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
      while (getline(str, word, CSV_DELIMITER)) {
        if (word == V_ENEMY) {
          if (rand() % 2 == 0) {
            word = V_ENEMYUP;
          } else {
            word = V_ENEMYDOWN;
          }
        }
        if (word == H_ENEMY) {
          if (rand() % 2 == 0) {
            word = H_ENEMYLEFT;
          } else {
            word = H_ENEMYRIGHT;
          }
        }
        row.push_back(word);
      }
      content.push_back(row);
    }
  }
  return content;
}
int read_game_time(string fname) {
  fstream file(fname, ios::in);
  string line;
  getline(file, line);
  int game_time = stoi(line);
  return game_time;
}
class Map {
  public: Map();
  void init_map();
  int get_game_time() {
    return game_time;
  }
  VVS get_map() {
    return map;
  }
  void set_map(VVS map1) {
    map = map1;
  }
  void update_enemy();
  private: VVS map;
  int game_time;
};
class Agent {
  public: Agent();
  void init_agent();
  pair < int,
  int > get_pos() {
    return pos;
  }
  void set_pos(pair < int, int > pos1) {
    pos = pos1;
  }
  int get_cnt_keys() {
    return cnt_keys;
  }
  pair < int,
  int > get_door() {
    return door;
  }
  int get_life() {
    return life;
  }
  pair < bool,
  time_t > get_power3() {
    return has_power3;
  }
  bool make_move(string command, VVS map);
  void plant_bomb();
  vector < pair < pair < int,
  int > ,
  time_t >> get_cnt_bomb() {
    return cnt_bomb;
  }
  VVS fire_bomb(VVS map);
  VVS collect(VVS map);
  void jiz_from_enemy(VVS map);
  private: pair < int,
  int > pos;
  int cnt_keys;
  pair < int,
  int > door;
  pair < bool,
  time_t > has_power3;
  vector < pair < pair < int,
  int > ,
  time_t >> cnt_bomb;
  int life;
};
void Agent::init_agent() {
  pos = make_pair(1, 1);
  cnt_keys = 0;
  has_power3 = make_pair(false, time(0));
  door = make_pair(-1, -1);
  life = 2;
}
Agent::Agent() {
  init_agent();
}
Map::Map() {
  init_map();
}
VVS init_keys_power(VVS map) {
  vector < pair < int, int >> wall_count;
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == WALL1) {
        wall_count.push_back(make_pair(i, j));
      }
    }
  }
  srand(time(0));
  vector < int > random_nums;
  while (random_nums.size() != wall_count.size()) {
    int num = rand() % wall_count.size();
    if (find(all(random_nums), num) == random_nums.end()) {
      random_nums.push_back(num);
    }
  }
  for (int i = 0; i < 3; i++) {
    map[wall_count[random_nums[i]].first][wall_count[random_nums[i]].second] = HIDE_KEY;
  }
  map[wall_count[random_nums[3]].first][wall_count[random_nums[3]].second] = HIDE_POWER2;
  map[wall_count[random_nums[4]].first][wall_count[random_nums[4]].second] = HIDE_POWER3;
  return map;
}
void Map::init_map() {
  map = read_record(MAP_PATH);
  game_time = read_game_time(MAP_PATH);
  map = init_keys_power(map);
}
void Map::update_enemy() {
  VVS map1;
  for (int i = 0; i < map.size(); i++) {
    vector < string > row;
    for (int j = 0; j < map[i].size(); j++) {
      row.push_back(EMPTY);
    }
    map1.push_back(row);
  }
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == V_ENEMYUP && map[i - 1][j] == EMPTY) map1[i - 1][j] = map[i][j];
      else if (map[i][j] == V_ENEMYUP && map[i - 1][j] != EMPTY) {
        map[i][j] = V_ENEMYDOWN;
        map1[i + 1][j] = map[i][j];
      } else if (map[i][j] == V_ENEMYDOWN && map[i + 1][j] == EMPTY) map1[i + 1][j] = map[i][j];
      else if (map[i][j] == V_ENEMYDOWN && map[i + 1][j] != EMPTY) {
        map[i][j] = V_ENEMYUP;
        map1[i - 1][j] = map[i][j];
      } else if (map[i][j] == H_ENEMYLEFT && map[i][j - 1] == EMPTY) map1[i][j - 1] = map[i][j];
      else if (map[i][j] == H_ENEMYLEFT && map[i][j - 1] != EMPTY) {
        map[i][j] = H_ENEMYRIGHT;
        map1[i][j + 1] = map[i][j];
      } else if (map[i][j] == H_ENEMYRIGHT && map[i][j + 1] == EMPTY) map1[i][j + 1] = map[i][j];
      else if (map[i][j] == H_ENEMYRIGHT && map[i][j + 1] != EMPTY) {
        map[i][j] = H_ENEMYLEFT;
        map1[i][j - 1] = map[i][j];
      }
      if (map[i][j] != EMPTY && map[i][j] != H_ENEMYRIGHT && map[i][j] != H_ENEMYLEFT && map[i][j] != V_ENEMYDOWN && map[i][j] != V_ENEMYUP) map1[i][j] = map[i][j];
    }
  }
  map = map1;
}
bool Agent::make_move(string command, VVS map) {
  if (command == "w" && map[pos.first - 1][pos.second] != DOOR && map[pos.first - 1][pos.second] != HIDE_POWER2 && map[pos.first - 1][pos.second] != HIDE_POWER3 && map[pos.first - 1][pos.second] != HIDE_KEY && map[pos.first - 1][pos.second] != WALL2 && map[pos.first - 1][pos.second] != WALL1) {
    return true;
  }
  if (command == "s" && map[pos.first + 1][pos.second] != DOOR && map[pos.first + 1][pos.second] != HIDE_POWER2 && map[pos.first + 1][pos.second] != HIDE_POWER3 && map[pos.first + 1][pos.second] != HIDE_KEY && map[pos.first + 1][pos.second] != WALL2 && map[pos.first + 1][pos.second] != WALL1) {
    return true;
  }
  if (command == "a" && map[pos.first][pos.second - 1] != DOOR && map[pos.first][pos.second - 1] != HIDE_POWER2 && map[pos.first][pos.second - 1] != HIDE_POWER3 && map[pos.first][pos.second - 1] != HIDE_KEY && map[pos.first][pos.second - 1] != WALL2 && map[pos.first][pos.second - 1] != WALL1) {
    return true;
  }
  if (command == "d" && map[pos.first][pos.second + 1] != DOOR && map[pos.first][pos.second + 1] != HIDE_POWER2 && map[pos.first][pos.second + 1] != HIDE_POWER3 && map[pos.first][pos.second + 1] != HIDE_KEY && map[pos.first][pos.second + 1] != WALL2 && map[pos.first][pos.second + 1] != WALL1) {
    return true;
  }
  return false;
}
void Agent::plant_bomb() {
  int count_bomb = 0;
  time_t start_count = time(0);
  for (int i = 0; i < cnt_bomb.size(); i++) {
    if (start_count - cnt_bomb[i].second <= 2) {
      count_bomb++;
    }
  }
  if (count_bomb < 3) {
    cnt_bomb.push_back(make_pair(pos, time(0)));
  }
}
VVS Agent::fire_bomb(VVS map) {
  time_t startt = time(0);

  for (int i = 0; i < cnt_bomb.size(); i++) {
    if (startt - cnt_bomb[i].second == 3) {
      int row = cnt_bomb[i].first.first;
      int col = cnt_bomb[i].first.second;
      if (map[row][col - 1] == HIDE_KEY || map[row][col - 1] == HIDE_POWER2 || map[row][col - 1] == HIDE_POWER3 || map[row][col - 1] == DOOR || map[row][col - 1] == WALL1) {
        transform(all(map[row][col - 1]), map[row][col - 1].begin(), ::tolower);
      }
      if (map[row][col + 1] == HIDE_KEY || map[row][col + 1] == HIDE_POWER2 || map[row][col + 1] == HIDE_POWER3 || map[row][col + 1] == DOOR || map[row][col + 1] == WALL1) {
        transform(all(map[row][col + 1]), map[row][col + 1].begin(), ::tolower);
      }
      if (map[row - 1][col] == HIDE_KEY || map[row - 1][col] == HIDE_POWER2 || map[row - 1][col] == HIDE_POWER3 || map[row - 1][col] == DOOR || map[row - 1][col] == WALL1) {
        transform(all(map[row - 1][col]), map[row - 1][col].begin(), ::tolower);
      }
      if (map[row + 1][col] == HIDE_KEY || map[row + 1][col] == HIDE_POWER2 || map[row + 1][col] == HIDE_POWER3 || map[row + 1][col] == DOOR || map[row + 1][col] == WALL1) {
        transform(all(map[row + 1][col]), map[row + 1][col].begin(), ::tolower);
      }
      if ((row - 1 == pos.first && col == pos.second) || (row + 1 == pos.first && col == pos.second) || (row == pos.first && col - 1 == pos.second) || (row == pos.first && col + 1 == pos.second) || (row == pos.first && col == pos.second)) {
        life -= 1;
      }
      if (map[row][col - 1] == V_ENEMYUP || map[row][col - 1] == V_ENEMYDOWN || map[row][col - 1] == H_ENEMYLEFT || map[row][col - 1] == H_ENEMYRIGHT) {
        map[row][col - 1] = EMPTY;
      }
      if (map[row][col + 1] == V_ENEMYUP || map[row][col + 1] == V_ENEMYDOWN || map[row][col + 1] == H_ENEMYLEFT || map[row][col + 1] == H_ENEMYRIGHT) {
        map[row][col + 1] = EMPTY;
      }
      if (map[row - 1][col] == V_ENEMYUP || map[row - 1][col] == V_ENEMYDOWN || map[row - 1][col] == H_ENEMYLEFT || map[row - 1][col] == H_ENEMYRIGHT) {
        map[row - 1][col] = EMPTY;
      }
      if (map[row + 1][col] == V_ENEMYUP || map[row + 1][col] == V_ENEMYDOWN || map[row + 1][col] == H_ENEMYLEFT || map[row + 1][col] == H_ENEMYRIGHT) {
        map[row + 1][col] = EMPTY;
      }
    }
  }
  return map;
}
VVS Agent::collect(VVS map) {
  if (map[pos.first][pos.second] == SHOW_DOOR) {
    door = pos;
  }
  if (map[pos.first][pos.second] == SHOW_KEY) {
    cnt_keys++;
    map[pos.first][pos.second] = EMPTY;
  }
  if (map[pos.first][pos.second] == SHOW_POWER2) {
    if (life < 3) {
      life += 1;
    }
    map[pos.first][pos.second] = EMPTY;
  }
  if (map[pos.first][pos.second] == SHOW_POWER3) {
    has_power3 = make_pair(true, time(0));
    map[pos.first][pos.second] = EMPTY;
  }
  return map;
}
void Agent::jiz_from_enemy(VVS map) {
  if (map[pos.first][pos.second] == V_ENEMYUP || map[pos.first][pos.second] == V_ENEMYDOWN || map[pos.first][pos.second] == H_ENEMYLEFT || map[pos.first][pos.second] == H_ENEMYRIGHT) {
    life -= 1;
  }
}
class Game {
  public: Game();
  void init_game();
  VVS get_map() {
    return board.get_map();
  }
  pair < int,
  int > get_agent_pos() {
    return agent.get_pos();
  }
  bool check_win(int cnt_keys, pair < int, int > door, pair < int, int > agent_pos);
  bool check_lose(int life);
  void turn();
  private: Map board;
  Agent agent;
  int end_game;

};
Game::Game() {
  init_game();
}
void Game::init_game() {
  end_game = 0;
}
bool Game::check_win(int cnt_keys, pair < int, int > door, pair < int, int > agent_pos) {
  if (cnt_keys == 3 && door == agent_pos) {
    return true;
  }
  return false;
}
bool Game::check_lose(int life) {
  if (life <= 0) {
    return true;
  }
  return false;
}
void map_graphic(sf::RenderWindow & window, VVS map, pair < int, int > pos, vector < pair < pair < int, int > , time_t >> cnt_bomb) {
  int row = map.size();
  int col = map[0].size();
  sf::Texture empty_texture, bomb_texture, textures[row][col];
  sf::Sprite empty_sprite, bomb_sprite, sprites[row][col];
  sf::Image grass_image, wall1_image, wall2_image, v_enemyup_image, v_enemydown_image, h_enemyleft_image, h_enemyright_image, key_image, power2_image, power3_image, door_image, bomb_image;
  if (!(grass_image.loadFromFile(GRASS_IMAGE))) cout << "Cannot load image";
  if (!(wall2_image.loadFromFile(WALL2_IMAGE))) cout << "Cannot load image";
  if (!(v_enemyup_image.loadFromFile(V_ENEMYUP_IMAGE))) cout << "Cannot load image";
  if (!(v_enemydown_image.loadFromFile(V_ENEMYDOWN_IMAGE))) cout << "Cannot load image";
  if (!(h_enemyleft_image.loadFromFile(H_ENEMYLEFT_IMAGE))) cout << "Cannot load image";
  if (!(h_enemyright_image.loadFromFile(H_ENEMYRIGHT_IMAGE))) cout << "Cannot load image";
  if (!(wall1_image.loadFromFile(WALL1_IMAGE))) cout << "Cannot load image";
  if (!(key_image.loadFromFile(KEY_IMAGE))) cout << "Cannot load image";
  if (!(power2_image.loadFromFile(POWER2_IMAGE))) cout << "Cannot load image";
  if (!(power3_image.loadFromFile(POWER3_IMAGE))) cout << "Cannot load image";
  if (!(door_image.loadFromFile(DOOR_IMAGE))) cout << "Cannot load image";
  if (!(bomb_image.loadFromFile(BOMB_IMAGE))) cout << "Cannot load image";
  empty_texture.loadFromImage(grass_image);
  bomb_texture.loadFromImage(bomb_image);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (map[i][j] == WALL2) {
        textures[i][j].loadFromImage(wall2_image);
      } else if (map[i][j] == V_ENEMYUP) {
        textures[i][j].loadFromImage(v_enemyup_image);
      } else if (map[i][j] == V_ENEMYDOWN) {
        textures[i][j].loadFromImage(v_enemydown_image);
      } else if (map[i][j] == H_ENEMYLEFT) {
        textures[i][j].loadFromImage(h_enemyleft_image);
      } else if (map[i][j] == H_ENEMYRIGHT) {
        textures[i][j].loadFromImage(h_enemyright_image);
      } else if (map[i][j] == WALL1 || map[i][j] == HIDE_KEY || map[i][j] == HIDE_POWER2 || map[i][j] == HIDE_POWER3 || map[i][j] == DOOR) {
        textures[i][j].loadFromImage(wall1_image);
      } else if (map[i][j] == SHOW_KEY) {
        textures[i][j].loadFromImage(key_image);
      } else if (map[i][j] == SHOW_POWER2) {
        textures[i][j].loadFromImage(power2_image);
      } else if (map[i][j] == SHOW_POWER3) {
        textures[i][j].loadFromImage(power3_image);
      } else if (map[i][j] == SHOW_DOOR) {
        textures[i][j].loadFromImage(door_image);
      }
      empty_sprite.setTexture(empty_texture);
      empty_sprite.setPosition(j * 50, i * 50);
      sprites[i][j].setTexture(textures[i][j]);
      sprites[i][j].setPosition(j * 50, i * 50);
      window.draw(empty_sprite);
      window.draw(sprites[i][j]);
    }
  }
  for (int i = 0; i < cnt_bomb.size(); i++) {
    if (time(0) - cnt_bomb[i].second <= 2) {
      bomb_sprite.setTexture(bomb_texture);
      bomb_sprite.setPosition(cnt_bomb[i].first.second * 50, cnt_bomb[i].first.first * 50);
      window.draw(bomb_sprite);
    }
  }

}
void text_graphic(sf::RenderWindow & window, int life, time_t gametime, int row, int col, int cnt_keys) {
  sf::Font font;
  font.loadFromFile("Pic/Arial.ttf");
  sf::Text text;
  text.setFont(font);
  text.setString("life:" + to_string(life));
  text.setCharacterSize(50);
  text.setFillColor(sf::Color::White);
  text.setPosition(0, 50 * row);
  window.draw(text);
  text.setString("time:" + to_string(gametime));
  text.setPosition(150, 50 * row);
  window.draw(text);
  text.setString("keys:" + to_string(cnt_keys));
  text.setPosition(350, 50 * row);
  window.draw(text);
}
void winlose_graphic(sf::RenderWindow & window, string str) {
  sf::Font font;
  font.loadFromFile("Pic/Arial.ttf");
  sf::Text text;
  text.setFont(font);
  text.setString(str);
  text.setCharacterSize(100);
  text.setFillColor(sf::Color::White);
  text.setPosition(200, 200);
  window.draw(text);
  window.display();
  sf::sleep(sf::milliseconds(10000));
}
void agent_graphic(sf::RenderWindow & window, pair < int, int > pos, string dir) {
  sf::Image agent_up_image, agent_down_image, agent_left_image, agent_right_image;
  if (!(agent_up_image.loadFromFile(AGENT_UP_IMAGE))) cout << "Cannot load image";
  if (!(agent_down_image.loadFromFile(AGENT_DOWN_IMAGE))) cout << "Cannot load image";
  if (!(agent_left_image.loadFromFile(AGENT_LEFT_IMAGE))) cout << "Cannot load image";
  if (!(agent_right_image.loadFromFile(AGENT_RIGHT_IMAGE))) cout << "Cannot load image";

  sf::Texture agent_texture;
  sf::Sprite agent_sprite;
  if (dir == "s") agent_texture.loadFromImage(agent_down_image);
  if (dir == "w") agent_texture.loadFromImage(agent_up_image);
  if (dir == "a") agent_texture.loadFromImage(agent_left_image);
  if (dir == "d") agent_texture.loadFromImage(agent_right_image);
  agent_sprite.setTexture(agent_texture);
  agent_sprite.setPosition(pos.second, pos.first);
  window.draw(agent_sprite);
}
void Game::turn() {
  sf::RenderWindow window(sf::VideoMode(50 * board.get_map()[0].size(), 50 * board.get_map().size() + 50), "BOZGHALE");
  time_t start, gametime;
  start = time(0);
  gametime = time(0);
  string dir = "w";
  pair < int, int > agent_pos = make_pair(50, 50);
  while (time(0) - gametime <= read_game_time(MAP_PATH) && window.isOpen()) {
    window.clear();
    sf::Event event;
    while (window.pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (agent.make_move("w", board.get_map())) {
          dir = "w";
          agent_pos.first -= 2;
        }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (agent.make_move("s", board.get_map())) {
          dir = "s";
          agent_pos.first += 2;
        }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (agent.make_move("a", board.get_map())) {
          dir = "a";
          agent_pos.second -= 2;
        }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (agent.make_move("d", board.get_map())) {
          dir = "d";
          agent_pos.second += 2;
        }
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::B) {
          agent.plant_bomb();
        }
      }
      if (event.type == sf::Event::Closed)
        window.close();
    }
    agent.set_pos(make_pair((int)((agent_pos.first + 12) / 50), (int)((agent_pos.second + 12) / 50)));
    map_graphic(window, board.get_map(), agent.get_pos(), agent.get_cnt_bomb());
    text_graphic(window, agent.get_life(), time(0) - gametime, board.get_map().size(), board.get_map()[0].size(), agent.get_cnt_keys());
    agent_graphic(window, agent_pos, dir);
    if (check_win(agent.get_cnt_keys(), agent.get_door(), agent.get_pos()) || check_lose(agent.get_life())) {
      break;
    }
    window.display();
    board.set_map(agent.collect(board.get_map()));

    if (time(0) - start == 1) {
      if (!agent.get_power3().first) {
        board.update_enemy();
      } else if (agent.get_power3().first && time(0) - agent.get_power3().second >= 10) {
        board.update_enemy();
      }
      agent.jiz_from_enemy(board.get_map());
      board.set_map(agent.fire_bomb(board.get_map()));
      start = start + 1;
    }
  }
  if (check_win(agent.get_cnt_keys(), agent.get_door(), agent.get_pos())) winlose_graphic(window, "YOU WIN");
  else {
    winlose_graphic(window, "YOU LOSE");
  }
}
int main() {
  Game game;
  game.turn();
  return 0;
}
