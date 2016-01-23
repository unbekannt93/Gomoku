#include "Player.hh"
#include "Field.hh"
#include "Engine.hh"
#include "Intersection.hh"

Player::Player(Field *f, sf::Sprite *pawn_s, pawn p) : _field(f), _pawn(pawn_s), _brain(Player::SLEEP),
					     _stoneKilled(0), _owner(p)
{

}

Player::~Player()
{

}

sf::Sprite		*Player::getPawn(){
  return (_pawn);
}

void			Player::drawOn(t_position po){
  _pawn->setPosition(po.x, po.y);
  _field->getEngine()->getRender()->draw(*_pawn);
}

void			Player::turnBegin(){
  _brain = Player::THINK;
}

Player::Brain		Player::getBrain() const{
  return (_brain);
}

bool			Player::haveFinished() const{
  return (_brain == Player::FINISHED || _brain == Player::WIN);
}

void			Player::sleep(){
  _brain = Player::SLEEP;
}

void			Player::hover(t_position pos){
  pos = _field->getPosition(_field->getId(pos));
  if (_field->hover(pos))
    _field->drawPawn(_owner, pos);
}

pawn			Player::getPawnPlayer() const{
  return (_owner);
}

int			Player::getStoneKilled() const{
  return (_stoneKilled);
}
