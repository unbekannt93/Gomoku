#include "Humain.hh"
#include "Field.hh"
#include "Patern.hh"

#include <iostream>

Humain::Humain(Field *f, sf::Sprite *s) : Player(f, s)
{

}

Humain::~Humain()
{

}

void			Humain::action(Intersection *i){
  Patern		*p = 0;
  Intersection		*pi = 0;

  if (!i || i->getOwner())
    return;
  if (!(_field->getArbitrator()->canPlace(this, i)))
    return;
  if (!_field->getArbitrator()->canPlace(i))
    return;
  i->setOwner(this);
  unsigned int n;

  while ((p = _field->getArbitrator()->killInter(i, &n))){
    if ((pi = p->getInterById(_field, i, n, 1)))
      pi->setOwner(0);
    if ((pi = p->getInterById(_field, i, n, 2)))
      pi->setOwner(0);
    _stoneKilled += 2;
  }
  if (_field->getArbitrator()->winInter(i) || _stoneKilled >= 10)
    _brain = Player::WIN;
  else
    _brain = Player::FINISHED;

}
