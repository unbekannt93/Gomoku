#ifndef FIELD_HH_
#define FIELD_HH_

#include <string>
#include "Intersection.hh"
#include "Click.hh"
#include "Arbitrator.hh"
#include "Engine.hh"

class Field
{
public:
  Field(Engine*);
  ~Field();
  void		setMouse(t_position);
  int		getId(t_position) const;
  Intersection	*getInter(t_position);
  Intersection	*getInter(int);
  void		hover(t_position);
  void		hover(int);
  void		hover(Intersection*);
  bool		put(t_position);
  bool		put(int);
  bool		put(Intersection*);
  void		draw();
private:
  Intersection	*_field[361];
  sf::Sprite	*_backGround;
  t_position	_mouse;
  Intersection	*_lastInter;
  Arbitrator	*_arbitrator;
  Engine	*_engine;
};

#endif
