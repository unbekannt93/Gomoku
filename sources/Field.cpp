#include "Field.hh"
#include "Engine.hh"
#include <iostream>

Field::Field(Engine *e) : _engine(e), _sizeInter(50)
{
  _arbitrator = new Arbitrator(this);
  for (int i = 0; i < 361; i++){
    _field[i] = new Intersection(i, this, _engine);
  }
  _backGround = _engine->getPack()->getSprite(2);
  _hover = _engine->getPack()->getSprite(1);
}

Field::~Field()
{
  delete (_hover);
  delete (_backGround);
  for (int i = 0; i < 361; i++){
    delete (_field[i]);
  }
}

void		Field::reset(){
  for (int i = 0; i < 361; i++){
    delete (_field[i]);
    _field[i] = new Intersection(i, this, _engine);
  }
  _lastInter = 0;
}

void		Field::setMouse(t_position pos){
  _mouse = pos;
}

int		Field::getId(t_position pos) const{
  return ((pos.x / _sizeInter) % 19 + (pos.y / _sizeInter) * 19);
}

Intersection	*Field::getInter(t_position pos){
  return (getInter(getId(pos)));
}

Intersection	*Field::getInter(){
  return (getInter(getId(_mouse)));
}

Intersection	*Field::getInter(int id){
  if (id < 0 || id > 360)
    return (0);
  return (_field[id]);
}

void		Field::hover(t_position pos){
  hover(getInter(pos));
}

void		Field::hover(int id){
  hover(getInter(id));
}

void		Field::hover(Intersection *i){
  if (!i || i->getOwner())
    return;
  t_position pos = i->getPosition();
  _hover->setPosition(pos.x, pos.y);
  _engine->getRender()->draw(*_hover);
}

bool		Field::put(t_position pos){
  return (put(getInter(pos)));
}

bool		Field::put(int id){
  return (put(getInter(id)));
}

bool		Field::put(Intersection *i){
  if (!i)
    return (false);
  // Arbitrator
  return (true);
}

void		Field::draw(){
  _engine->getRender()->draw(*_backGround);

  for (int i = 0; i < 361; i++){
    _field[i]->draw();
  }
}

Engine		*Field::getEngine(){
  return (_engine);
}

Arbitrator	*Field::getArbitrator(){
  return (_arbitrator);
}
