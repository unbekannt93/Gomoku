#ifndef PATERN_HH_
#define PATERN_HH_

#include <string>
#include "Click.hh"
#include "Field.hh"
#include "Intersection.hh"

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
  bool		match(Field*, Intersection*);
  Intersection	*getNext(Field*, Intersection*, t_position);
  Intersection	*getNext(Field*, Intersection*, int, int);
  Intersection	*getNext(Field*, Intersection*, unsigned int);
  Intersection	*getInterById(Field*, Intersection*, unsigned int, unsigned int);
  t_position	subPosition(t_position, t_position);
  bool		matchInter(Player*, Intersection*, PaternCase);
  bool		matchWithId(Field*, Intersection*, unsigned int);
private:
  std::vector<PaternCase>	_patern;
};

#endif
