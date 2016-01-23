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
  bool		canPlace(Player*, char*);
  bool		playerWin(Player*);
  Patern	*winInter(char*);
  Patern	*blockInter(char*);
  Patern	*killInter(char*, unsigned int* = 0);

  void		initWinPatern();
  void		initKillPatern();
  void		initBlockPatern();

  bool		canPlace(char*);
  Intersection	*getInterPos(Field*, char*, int, int);
private:
  Field			*_field;
  std::vector<Patern>	_winPatern;
  std::vector<Patern>	_killPatern;
  std::vector<Patern>	_blockPatern;
};

#endif
