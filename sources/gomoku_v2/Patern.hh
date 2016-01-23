#ifndef PATERN_HH_
#define PATERN_HH_

#include <string>
#include <iostream>

#include "Click.hh"
#include "Field.hh"
#include "Gomoku.hh"

class Patern
{
public:
  struct	PaternCase{
    t_position	pos;
    int		player;
  };

public:
  Patern(int);
  ~Patern();
  void		addCase(t_position, int = 0);
  void		addCase(int, int, int = 0);


  bool		match(Field*, t_position, pawn, int = 0, unsigned int *p = 0);

  t_position	subPosition(t_position, t_position);
  t_position	addPosition(t_position, t_position);
  bool		matchInter(Patern::PaternCase, pawn, pawn);
  unsigned int	getSize();

  Patern::PaternCase	*getCase(unsigned int);


  pawn		*getPawnInBoard(Field*, pawn*, t_position);
  unsigned int	matchPercent(Field*, pawn*, t_position, pawn);
  unsigned int	matchMax(Field*, pawn*, t_position, pawn, int = 0);
private:
  std::vector<PaternCase>	_patern;
};

#endif
