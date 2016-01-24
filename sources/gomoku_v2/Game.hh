#ifndef GAME_HH_
#define GAME_HH_

#include <string>
#include <SFML/Graphics.hpp>
#include "Module.hh"
#include "Artificial.hh"
#include "Humain.hh"
#include "Field.hh"
#include "AButton.hh"
#include "RuleMenu.hh"

class Engine;

class Game : public Module
{
public:
  Game(Engine*, std::size_t, std::size_t);
  ~Game();
  void drawModule();
  void eventModule();
  void updateModule();
  void closeModule();
  void openModule();
  void setPosition(int, int);
  void reset();

  std::string	valueOf(int);
private:
  int		_winner;
  Field		_field;
  Player	*_players[2];
  int		_currentPlayer;
  sf::Sprite	*_backEnd[2];
  AButton	_exit;
  AButton	_new;
  bool		_openTools;
  RuleMenu	_rules;

  sf::Font	_font;
  sf::Text	_text;

  bool		_scoring;
};

#endif
