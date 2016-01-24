#include "Humain.hh"
#include "Field.hh"
#include "Patern.hh"

#include <iostream>

Humain::Humain(Field *f, sf::Sprite *s, pawn p) : Player(f, s, p)
{

}

Humain::~Humain()
{

}

void			Humain::action(t_position position){

  position = _field->getPosition(_field->getId(position));
  pawn			*p = _field->getInter(position);
  if (!_field->legalArgument(position) || !p || !PAWN((*p), 0) ||
      !_field->getArbitrator()->canPlace(this, position))
    return;

  //_field->setPawn(position, _owner);
  _field->setPawn(position, this);
  /*
  unsigned int		n;

  Patern *pat = 0;
  unsigned int i = 0;
  while ((pat = _field->getArbitrator()->getKillInter(i))){
    while (pat->match(_field, position, *p, 0, &n)){
      p = _field->getArbitrator()->getInterPawn(_field, pat, position, n, 1);
      if (p)
	*p = 0;
      p = _field->getArbitrator()->getInterPawn(_field, pat, position, n, 2);
      if (p)
	*p = 0;
      _stoneKilled += 2;
      p = _field->getInter(position);
    }
    i++;
  }
  */

  if (_field->getArbitrator()->playerWin(this, position) || _stoneKilled >= 10)
    _brain = Player::WIN;
  else
    _brain = Player::FINISHED;
}
