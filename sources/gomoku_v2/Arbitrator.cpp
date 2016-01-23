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
  initThreePatern();

  _rules[0] = true;
  _rules[1] = false;
  _rules[2] = true;
  _rules[3] = true;
}

Arbitrator::~Arbitrator()
{

}

bool		Arbitrator::threeOk(Player *p, t_position pos){
  if (!p)
    return (false);
  unsigned int n = 0;
  for (unsigned int i = 0; i < _threePatern.size(); i++){
    if (_threePatern[i].match(_field, pos, p->getPawnPlayer()))
      n++;
  }
  return (n <= 1);  
}

bool		Arbitrator::blockOk(Player *p, t_position pos){
  (void)p;
  (void)pos;
  return (true);
}

bool		Arbitrator::canPlace(Player *p, t_position pos){
  return ((!_rules[Arbitrator::THREE] || threeOk(p, pos)) &&
	  (!_rules[Arbitrator::BLOCK] || blockOk(p, pos)));
	  
}

bool		Arbitrator::playerWin(Player *p){
  if (!p)
    return (false);

  return (false);
}

bool		Arbitrator::playerWin(Player *player, t_position pos){
  return ((_rules[Arbitrator::STONES] && player->getStoneKilled() >= 10) ||
	  winInter(&pos));
}

Patern		*Arbitrator::winInter(t_position *inter){
  if (!inter)
    return (0);
  pawn *owner = _field->getInter(*inter);
  if (!owner)
    return (0);
  for (unsigned int i = 0; i < _winPatern.size(); i++){
    if (_winPatern[i].match(_field, _field->getPosition(_field->getId(*inter)), *owner))
      return (&_winPatern[i]);
  }
  return (0);
}

t_position	*Arbitrator::getInterPos(Field *f, t_position *pos, int x, int y){
  pos->x += x;
  pos->y += y;
  if (!f || !f->legalArgument(*pos))
    return (0);
  return (pos);
}

pawn		*Arbitrator::getInterPawn(Field *f, Patern *p, t_position pos, unsigned int ipos, unsigned int w){
  Patern::PaternCase *pc = p->getCase(ipos);
  Patern::PaternCase *pw = p->getCase(w);
  if (!pc || !pw)
    return (0);
  return (f->getInter(p->addPosition(p->subPosition(pc->pos, pw->pos), pos)));
}

Patern		*Arbitrator::getKillInter(unsigned int i){
  if (i >= _killPatern.size())
    return (0);
  return (&_killPatern[i]);
}

Patern		*Arbitrator::getWinInter(unsigned int i){
  if (i >= _winPatern.size())
    return (0);
  return (&_winPatern[i]);
}

Patern		*Arbitrator::getThreeInter(unsigned int i){
  if (i >= _threePatern.size())
    return (0);
  return (&_threePatern[i]);
}

Patern		*Arbitrator::killInter(t_position *inter){
  if (!inter)
    return (0);
  pawn *owner = _field->getInter(*inter);
  if (!owner)
    return (0);
  for (unsigned int i = 0; i < _winPatern.size(); i++){
    if (_killPatern[i].match(_field, _field->getPosition(_field->getId(*inter)), *owner))
      return (&_killPatern[i]);
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

void		Arbitrator::initThreePatern(){
  Patern	p(0);

  p.addCase(1, 0, 3);
  p.addCase(2, 0, 0);
  p.addCase(3, 0, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(1, 0, 0);
  p.addCase(2, 0, 3);
  p.addCase(3, 0, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(0, 1, 0);
  p.addCase(0, 2, 3);
  p.addCase(0, 3, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(0, 1, 3);
  p.addCase(0, 2, 0);
  p.addCase(0, 3, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(1, 1, 3);
  p.addCase(2, 2, 0);
  p.addCase(3, 3, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(1, 1, 0);
  p.addCase(2, 2, 3);
  p.addCase(3, 3, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(1, -1, 3);
  p.addCase(2, -2, 0);
  p.addCase(3, -3, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(1, -1, 0);
  p.addCase(2, -2, 3);
  p.addCase(3, -3, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(1, -1, 0);
  p.addCase(2, -2, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(1, 1, 0);
  p.addCase(2, 2, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(1, 0, 0);
  p.addCase(2, 0, 0);
  _threePatern.push_back(p);

  p = Patern(0);
  p.addCase(0, 1, 0);
  p.addCase(0, 2, 0);
  _threePatern.push_back(p);
}

/*
void		Arbitrator::initBreakFivePatern(){
  Patern	p(1);

  p.addCase(1, 0, 0);
  p.addCase(2, 0, 0);
  p.addCase(3, 0, 1);
  _blockPatern.push_back(p);
}
*/
