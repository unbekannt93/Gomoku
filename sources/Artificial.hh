#ifndef ARTIFICIAL_HH_
#define ARTIFICIAL_HH_

#include <string>
#include "Player.hh"

class Artificial : public Player
{
public:
  Artificial(Field*, sf::Sprite*);
  ~Artificial();
  void		action(Intersection*);
};

#endif
