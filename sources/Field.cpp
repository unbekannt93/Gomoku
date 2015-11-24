#include "Field.hh"

Field::Field(Engine *e) : _engine(e)
{
  for (int i = 0; i < 361; i++){
    _field[i] = new Intersection(i, this, _engine);
  }
}

Field::~Field()
{
  for (int i = 0; i < 361; i++){
    delete (_field[i]);
  }
}

void		Field::setMouse(t_position pos){
  _mouse = pos;
}

int		Field::getId(t_position pos) const{
  return ((pos.x / 50) % 19 + (pos.y / 50) * 19);
}

Intersection	*Field::getInter(t_position pos){
  return (getInter(getId(pos)));
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
  if (i)
    i->setHover();
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
