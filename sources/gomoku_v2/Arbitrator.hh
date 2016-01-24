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
    FIVE = 0,
    THREE = 1,
    BLOCK = 2,
    STONES = 3
  };
public:
  Arbitrator(Field*);
  ~Arbitrator();
  bool		canPlace(pawn, t_position);
  bool		playerWin(Player*);

  Patern	*winInter(t_position*, unsigned int *p = 0);

  Patern	*killInter(t_position*);
  Patern	*getKillInter(unsigned int);
  Patern	*getWinInter(unsigned int);
  Patern	*getThreeInter(unsigned int);

  void		initWinPatern();
  void		initKillPatern();
  void		initThreePatern();
  void		initBreakFivePatern();

  bool		dontBreak(Patern*, t_position, unsigned int);
  bool		tryBreak(t_position, pawn);

  t_position	*getInterPos(Field*, t_position*, int, int);

  pawn		*getInterPawn(Field*, Patern*, t_position, unsigned int, unsigned int);

  bool		threeOk(pawn, t_position);
  bool		blockOk(pawn, t_position);

  bool		playerWin(Player*, t_position);

  bool		getRule(int);
  void		setRule(int, bool);

  int		getLevelAI() const;
  void		setLevelAI(int);
private:
  Field			*_field;
  std::vector<Patern>	_winPatern;
  std::vector<Patern>	_killPatern;
  std::vector<Patern>	_breakPatern;
  std::vector<Patern>	_threePatern;
  bool			_rules[4];
  int			_levelAI;
};

#endif
