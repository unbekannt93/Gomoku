#ifndef PLAYER_HH_
#define PLAYER_HH_

#include <string>
#include <SFML/Graphics.hpp>
#include "Click.hh"
#include "Gomoku.hh"

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
  Player(Field*, sf::Sprite*, pawn);
  virtual	~Player();
  sf::Sprite	*getPawn();
  void		drawOn(t_position);
  virtual void	action(t_position) = 0;
  virtual void	turnBegin();
  Brain		getBrain() const;
  bool		haveFinished() const;
  void		sleep();
  void		hover(t_position);
  pawn		getPawnPlayer() const;
  int		getStoneKilled() const;
  void		addStone(int = 2);
  int		getLastPawn() const;
  void		setLastPawn(int);
protected:
  Field		*_field;
  sf::Sprite	*_pawn;
  Brain		_brain;
  int		_stoneKilled;
  pawn		_owner;
  int		_lastPawn;
};

#endif
