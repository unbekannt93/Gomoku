#include "Patern.hh"
#include <iostream>

Patern::Patern(int player)
{
  addCase(0, 0, player);
}

Patern::~Patern()
{

}

void		Patern::addCase(t_position pos, int player){
  addCase(pos.x, pos.y, player);
}

void		Patern::addCase(int x, int y, int player){
  Patern::PaternCase	p;

  p.pos.x = x * 50;
  p.pos.y = y * 50;
  p.player = player;
  _patern.push_back(p);
}

bool		Patern::match(Field *f, Intersection *inter){
  if (!f || !inter)
    return (false);
  for (unsigned int i = 0; i < _patern.size(); i++){
    if (matchWithId(f, inter, i))
      return (true);
  }
  return (false);
}

Intersection	*Patern::getNext(Field *f, Intersection *inter, t_position pos){
  return (getNext(f, inter, pos.x, pos.y));
}

Intersection	*Patern::getNext(Field *f, Intersection *inter, int x, int y){
  if (!f || !inter)
    return (0);
  t_position p = inter->getPosition();
  p.x += x;
  p.y += y;
  return (f->getInter(p));
}

Intersection	*Patern::getNext(Field *f, Intersection *inter, unsigned int id){
  if (id >= _patern.size())
    return (0);
  return (getNext(f, inter, _patern[id].pos));
}

Intersection	*Patern::getInterById(Field *f, Intersection *begin, unsigned int iam, unsigned int id){
  if (id >= _patern.size() || iam >= _patern.size())
    return (0);
  return (getNext(f, begin, subPosition(_patern[iam].pos, _patern[id].pos)));
}

t_position	Patern::subPosition(t_position a, t_position b){
  b.x -= a.x;
  b.y -= a.y;
  return (b);
}

bool		Patern::matchInter(Player *p, Intersection *a, Patern::PaternCase c){
  Player	*owner = a->getOwner();
  if (!a)
    return (false);
  if (c.player == 0){
    return (owner && p && p == owner);
  }else if (c.player == 1){
    return (owner && p && p != owner);
  }else if (c.player == 2){
    return (p && owner);
  }else if (c.player == 3){
    return (!p && !owner);
  }
  return (true);
}

bool		Patern::matchWithId(Field *f, Intersection *inter, unsigned int id){
  if (!f || !inter || id >= _patern.size())
    return (false);
  Intersection	*p = 0;
  for (unsigned int i = 0; i < _patern.size(); i++){
    p = getNext(f, inter, subPosition(_patern[id].pos, _patern[i].pos));
    if (!p){
      return (false);
    }
    if (!matchInter(inter->getOwner(), p, _patern[i]))
      return (false);
  }
  return (true);
}
