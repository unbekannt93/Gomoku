#ifndef PLAYER_HH_
#define PLAYER_HH_

#include <string>
#include <SFML/Graphics.hpp>
#include "Click.hh"

class Field;
class Intersection;

class Player
{
public:
  enum		Brain{
    SLEEP,
    THINK,
    FINISHED,
    WIN
  };

public:
  Player(Field*, sf::Sprite*);
  virtual	~Player();
  sf::Sprite	*getPawn();
  void		drawOn(t_position);
  virtual void	action(Intersection*) = 0;
  virtual void	turnBegin();
  Brain		getBrain() const;
  bool		haveFinished() const;
  void		sleep();
  void		hover(t_position);
protected:
  Field		*_field;
  sf::Sprite	*_pawn;
  Brain		_brain;
  int		_stoneKilled;
};

#endif
