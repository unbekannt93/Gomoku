#ifndef GAME_HH_
#define GAME_HH_

#include <string>
#include "Module.hh"
#include "Artificial.hh"
#include "Humain.hh"
#include "Field.hh"

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
private:
  Field		_field;
  Player	*_players[2];
  int		_currentPlayer;
};

#endif
