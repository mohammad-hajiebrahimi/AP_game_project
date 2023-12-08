
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
