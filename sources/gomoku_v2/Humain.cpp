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
      !_field->getArbitrator()->canPlace(_owner, position))
    return;
  _field->setPawn(position, this);
  if (_field->getArbitrator()->playerWin(this, position))
    _brain = Player::WIN;
  else
    _brain = Player::FINISHED;
}
