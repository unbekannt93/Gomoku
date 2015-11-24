#include "Player.hh"
#include "Field.hh"
#include "Engine.hh"
#include "Intersection.hh"

Player::Player(Field *f, sf::Sprite *pawn) : _field(f), _pawn(pawn), _brain(Player::SLEEP),
					     _stoneKilled(0)
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
