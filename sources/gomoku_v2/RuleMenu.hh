#ifndef RULEMENU_HH_
#define RULEMENU_HH_

#include <string>
#include <SFML/Graphics.hpp>

class Game;
class Engine;
class Field;

class RuleMenu
{
public:
  RuleMenu(Engine*, Field*);
  ~RuleMenu();
  void		draw();
  void		event();
private:
  Engine	*_engine;
  Field		*_field;
  sf::Sprite	*_back;
  sf::CircleShape	_point;
  sf::CircleShape	_stagePoint;

  sf::Vector2f	_rules[4][2];
  int		_stage;
};

#endif
