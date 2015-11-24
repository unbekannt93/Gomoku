#ifndef INTERSECTION_HH_
#define INTERSECTION_HH_

#include <string>
#include <SFML/Graphics.hpp>
#include "Click.hh"

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
private:
  int		_id;
  t_position	_position;
  Field		*_field;
  Engine	*_engine;
  bool		_hover;
  sf::Sprite	*_pict;
  sf::Sprite	*_hoverPict;
};

#endif
