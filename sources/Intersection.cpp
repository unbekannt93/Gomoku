#include "Intersection.hh"
#include "Engine.hh"
#include "Field.hh"

Intersection::Intersection(int id, Field *f, Engine *e) : _id(id),
							  _field(f), _engine(e)
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

bool		Intersection::isHover() const{
  return (_hover);
}

void		Intersection::draw(){
  if (_hover)
    _engine->getRender()->draw(*_hoverPict);
  _engine->getRender()->draw(*_pict);
}

void		Intersection::setHover(){
  _hover = true;
}
