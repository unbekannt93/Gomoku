#ifndef ARTIFICIAL_HH_
#define ARTIFICIAL_HH_

#include <string>
#include "Player.hh"

class ABTree;

class Artificial : public Player
{
public:
  Artificial(Field*, sf::Sprite*, pawn, int = 3);
  ~Artificial();
  void		action(t_position);
  void		turnBegin();
  void		think();
private:
  int		_depth;
  ABTree	*_tree;
};

#endif
