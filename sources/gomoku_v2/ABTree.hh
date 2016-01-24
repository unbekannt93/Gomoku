#ifndef ABTREE_HH_
#define ABTREE_HH_

#include <string>
#include <vector>
#include "Click.hh"
#include "Gomoku.hh"
#include "Patern.hh"

class Field;

class ABTree
{
public:
  ABTree(Field*, ABTree*, int, pawn, int, int, bool = true, int = 3);
  ABTree(Field*, pawn, bool = true, int = 3);
  ~ABTree();
  int	buildTree();
  void	setHexaInterest(pawn, bool = true);
  void	setInterest(int, bool);
  bool	myInterest(pawn);
  int	getScore();
  int	getIdChild() const;
  int	getId() const;
private:
  Field		*_field;
  ABTree	*_parent;
  t_position	_position;
  int		_id;
  pawn		_player;
  int		_min;
  int		_max;
  bool		_isMax;
  int		_depth;
  int		_score;
  std::vector<ABTree*>	_children;
  ABTree	*_child;
};

#endif
