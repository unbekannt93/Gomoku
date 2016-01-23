#ifndef HUMAIN_HH_
#define HUMAIN_HH_

#include <string>
#include "Player.hh"

class Humain : public Player
{
public:
  Humain(Field*, sf::Sprite*, pawn);
  ~Humain();
  void		action(t_position);
};

#endif
