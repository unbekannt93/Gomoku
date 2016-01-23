#include "Arbitrator.hh"
#include "Field.hh"
#include "Player.hh"
#include "Intersection.hh"
#include "Patern.hh"

Arbitrator::Arbitrator(Field *f) : _field(f)
{
  initWinPatern();
  initKillPatern();
  initBlockPatern();
}

Arbitrator::~Arbitrator()
{

}

bool		Arbitrator::canPlace(Player *p, char *i){
  if (!p || !i)
    return (false);
  
  return (true);
}

bool		Arbitrator::playerWin(Player *p){
  if (!p)
    return (false);

  return (false);
}

Patern		*Arbitrator::winInter(char *inter){
  if (!inter || *inter == 2)
    return (0);
  for (unsigned int i = 0; i < _winPatern.size(); i++){
    if (_winPatern[i].match(_field, inter))
      return (&_winPatern[i]);
  }
  return (0);
}

Patern		*Arbitrator::blockInter(char *inter){
  if (!inter || *inter == 2)
    return (0);
  for (unsigned int i = 0; i < _blockPatern.size(); i++){
    if (_blockPatern[i].match(_field, inter))
      return (&_blockPatern[i]);
  }
  return (0);
}

bool		Arbitrator::canPlace(char *inter){
  char	*l = getInterPos(_field, inter, -50, 0);
  char	*r = getInterPos(_field, inter, 50, 0);
  char	*t = getInterPos(_field, inter, 0, -50);
  char	*b = getInterPos(_field, inter, 0, 50);
  
  if (!l || !r || !t || !b)
    return (false);
  return (!(!inter->getOwner() && l->getOwner() && r->getOwner() && t->getOwner() && b->getOwner()));
}


Intersection	*Arbitrator::getInterPos(Field *f, char *inter, int x, int y){
  if (!f || *inter == 2)
    return (0);
  t_position p = inter->getPosition();
  p.x += x;
  p.y += y;
  return (f->getInter(p));
}

Patern		*Arbitrator::killInter(Intersection *inter, unsigned int *ptr){
  if (!inter || !inter->getOwner())
    return (0);
  for (unsigned int i = 0; i < _killPatern.size(); i++){
    if (_killPatern[i].matchWithId(_field, inter, 0)){
      if (ptr)
	*ptr = 0;
      return (&_killPatern[i]);
    }else if (_killPatern[i].matchWithId(_field, inter, 3)){
      if (ptr)
	*ptr = 3;
      return (&_killPatern[i]);
    }
  }
  return (0);
}

void		Arbitrator::initWinPatern(){
  Patern p(0);
  p.addCase(1, 0);
  p.addCase(2, 0);
  p.addCase(3, 0);
  p.addCase(4, 0);
  _winPatern.push_back(p);

  p = Patern(0);
  p.addCase(0, 1);
  p.addCase(0, 2);
  p.addCase(0, 3);
  p.addCase(0, 4);
  _winPatern.push_back(p);

  p = Patern(0);
  p.addCase(1, 1);
  p.addCase(2, 2);
  p.addCase(3, 3);
  p.addCase(4, 4);
  _winPatern.push_back(p);

  p = Patern(0);
  p.addCase(1, -1);
  p.addCase(2, -2);
  p.addCase(3, -3);
  p.addCase(4, -4);
  _winPatern.push_back(p);
}

void		Arbitrator::initKillPatern(){
  Patern	p(0);
  p.addCase(1, 0, 1);
  p.addCase(2, 0, 1);
  p.addCase(3, 0, 0);
  _killPatern.push_back(p);

  p = Patern(0);
  p.addCase(0, 1, 1);
  p.addCase(0, 2, 1);
  p.addCase(0, 3, 0);
  _killPatern.push_back(p);

  p = Patern(0);
  p.addCase(1, 1, 1);
  p.addCase(2, 2, 1);
  p.addCase(3, 3, 0);
  _killPatern.push_back(p);

  p = Patern(0);
  p.addCase(1, -1, 1);
  p.addCase(2, -2, 1);
  p.addCase(3, -3, 0);
  _killPatern.push_back(p);
}

void		Arbitrator::initBlockPatern(){
  Patern	p(1);
  p.addCase(2, 0, 1);
  p.addCase(1, 1, 1);
  p.addCase(1, -1, 1);
  p.addCase(1, 0, 3);
  _blockPatern.push_back(p);
}
