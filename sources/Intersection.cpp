#include "Intersection.hh"
#include "Engine.hh"
#include "Field.hh"

Intersection::Intersection(int id, Field *f, Engine *e) : _id(id),
							  _field(f), _engine(e), _owner(0)
{
  _position.x = _id % 19 * 50;
  _position.y = _id / 19 * 50;
}

Intersection::~Intersection()
{

}

int		Intersection::getId() const{
  return (_id);
}

t_position	Intersection::getPosition() const{
  return (_position);
}

void		Intersection::draw(){
  if (_owner)
    _owner->drawOn(_position);
}

void		Intersection::setOwner(Player *p){
  _owner = p;
}

Player		*Intersection::getOwner(){
  return (_owner);
}
