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
