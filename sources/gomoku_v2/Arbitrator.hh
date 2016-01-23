#ifndef ARBITRATOR_HH_
#define ARBITRATOR_HH_

#include <string>
#include <vector>
#include <iostream>

#include "Click.hh"
#include "Gomoku.hh"

class Patern;
class Field;
class Intersection;
class Player;

class Arbitrator
{
public:
  enum		Rules{
    THREE = 0,
    STONES = 1,
    FIVE = 2,
    BLOCK = 3
  };
public:
  Arbitrator(Field*);
  ~Arbitrator();
  bool		canPlace(Player*, t_position);
  bool		playerWin(Player*);

  Patern	*winInter(t_position*);

  Patern	*killInter(t_position*);
  Patern	*getKillInter(unsigned int);
  Patern	*getWinInter(unsigned int);
  Patern	*getThreeInter(unsigned int);

  void		initWinPatern();
  void		initKillPatern();
  void		initBlockPatern();
  void		initThreePatern();
  t_position	*getInterPos(Field*, t_position*, int, int);

  pawn		*getInterPawn(Field*, Patern*, t_position, unsigned int, unsigned int);

  bool		threeOk(Player*, t_position);
  bool		blockOk(Player*, t_position);

  bool		playerWin(Player*, t_position);

private:
  Field			*_field;
  std::vector<Patern>	_winPatern;
  std::vector<Patern>	_killPatern;
  std::vector<Patern>	_blockPatern;
  std::vector<Patern>	_threePatern;
  bool			_rules[4];
};

#endif
