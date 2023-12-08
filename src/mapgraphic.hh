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
