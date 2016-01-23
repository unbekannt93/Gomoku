#ifndef HUMAIN_HH_
#define HUMAIN_HH_

#include <string>
#include "Player.hh"

class Humain : public Player
{
public:
  Humain(Field*, sf::Sprite*);
  ~Humain();
  void		action(Intersection*);
};

#endif
