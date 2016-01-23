#ifndef FIELD_HH_
#define FIELD_HH_

#include <string>
#include "Intersection.hh"
#include "Click.hh"
#include "Arbitrator.hh"
#include "Gomoku.hh"

class Engine;

class Field
{
public:
  Field(Engine*);
  ~Field();
  void		setMouse(t_position);
  int		getId(t_position) const;
  pawn		*getInter();
  pawn		*getInter(t_position);
  pawn		*getInter(int);
  bool		hover(t_position);
  bool		hover(int);
  bool		put(t_position);
  bool		put(int);
  void		draw();
  Engine	*getEngine();
  Arbitrator	*getArbitrator();
  void		reset();
  bool		legalArgument(int) const;
  bool		legalArgument(t_position) const;
  t_position	getPosition(int) const;
  void		drawPawn(pawn, t_position);
  bool		setPawn(t_position, pawn);
  t_position	*getCopyPosition(t_position);
  void		setCase(pawn*, pawn);
  void		drawMonster(t_position);
  t_position	addPosition(t_position, int, int);
  void		setHexaInterest(t_position);
  void		setInterest(t_position);
  pawn		*getBoard(bool = true);
private:
  pawn		_field[361];
  sf::Sprite	*_backGround;
  sf::Sprite	*_hover;
  sf::Sprite	*_monster;
  t_position	_mouse;
  t_position	_lastInter;
  Engine	*_engine;
  Arbitrator	*_arbitrator;
  int		_sizeInter;
  sf::Sprite	*_pawns[2];
};

#endif
