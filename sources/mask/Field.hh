#ifndef FIELD_HH_
#define FIELD_HH_

#include <string>
#include "Intersection.hh"
#include "Click.hh"
#include "Arbitrator.hh"

class Engine;

class Field
{
public:
  Field(Engine*);
  ~Field();
  void		setMouse(t_position);
  int		getId(t_position) const;
  char		*getInter();
  char		*getInter(t_position);
  char		*getInter(int);
  void		hover(t_position);
  void		hover(int);
  void		hover(char*);
  bool		put(t_position);
  bool		put(int);
  bool		put(char*);
  void		draw();
  Engine	*getEngine();
  Arbitrator	*getArbitrator();
  void		reset();
  t_position	getPos(int);
private:
  char		_field[361];
  sf::Sprite	*_backGround;
  sf::Sprite	*_hover;
  t_position	_mouse;
  Intersection	*_lastInter;
  Engine	*_engine;
  Arbitrator	*_arbitrator;
  int		_sizeInter;
};

#endif
