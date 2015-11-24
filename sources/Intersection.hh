#ifndef INTERSECTION_HH_
#define INTERSECTION_HH_

#include <string>
#include "Click.hh"
#include "Player.hh"

class Field;
class Engine;

class Intersection
{
public:
  Intersection(int, Field*, Engine*);
  ~Intersection();
  int		getId() const;
  t_position	getPosition() const;
  bool		isHover() const;
  void		draw();
  void		setHover();
  void		setOwner(Player*);
  Player	*getOwner();
private:
  int		_id;
  t_position	_position;
  Field		*_field;
  Engine	*_engine;
  bool		_hover;
  Player	*_owner;
};

#endif
