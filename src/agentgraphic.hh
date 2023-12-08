#ifndef AGENTGRAPHIC
#define AGENTGRAPHIC
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
#endif
