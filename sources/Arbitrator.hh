#ifndef ARBITRATOR_HH_
#define ARBITRATOR_HH_

#include <string>
#include <vector>

class Patern;
class Field;
class Intersection;
class Player;

class Arbitrator
{
public:
  Arbitrator(Field*);
  ~Arbitrator();
  bool		canPlace(Player*, Intersection*);
  bool		playerWin(Player*);
  Patern	*winInter(Intersection*);
  Patern	*blockInter(Intersection*);
  Patern	*killInter(Intersection*, unsigned int* = 0);

  void		initWinPatern();
  void		initKillPatern();
  void		initBlockPatern();

  bool		canPlace(Intersection*);
  Intersection	*getInterPos(Field*, Intersection*, int, int);
private:
  Field			*_field;
  std::vector<Patern>	_winPatern;
  std::vector<Patern>	_killPatern;
  std::vector<Patern>	_blockPatern;
};

#endif
