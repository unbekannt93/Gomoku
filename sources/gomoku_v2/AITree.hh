#ifndef AITREE_HH_
#define AITREE_HH_

#include <string>
#include <vector>
#include "Gomoku.hh"
#include "Click.hh"
#include "Player.hh"
#include <SFML/System.hpp>

class			Field;

class			AITree
{
public:
  AITree(Field*, pawn, pawn*, int = 3);
  AITree(Field*, pawn, pawn*, t_position, int, bool);
  AITree(Field*, pawn, pawn*, int, int, bool);
  ~AITree();
  void			buildTree();
  void			setHexaInterest(int);
  void			setInterest(int);
  pawn			*copyBoard();
  void			getPoints();
  void			wait();
  int			getPoints() const;
  AITree		*getBetter(int = (-gl_infini), int = gl_infini);
  bool			isEnd() const;
private:
  Field			*_field;
  pawn			_player;
  pawn			*_board;
  int			_points;
  int			_depth;
  int			_id;
  std::vector<AITree*>	_branch;
  sf::Thread		_th;
  bool			_max;
};

#endif
