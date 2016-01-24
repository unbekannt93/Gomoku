#include "Field.hh"
#include "Engine.hh"
#include <iostream>
#include "Patern.hh"

Field::Field(Engine *e) : _engine(e), _sizeInter(50), _drawMonster(false)
{
  _arbitrator = new Arbitrator(this);
  for (int i = 0; i < 361; i++){
    _field[i] = gl_empty;
  }
  _backGround = _engine->getPack()->getSprite(2);
  _hover = _engine->getPack()->getSprite(1);
  _monster = _engine->getPack()->getSprite(8);

  _pawns[0] = _engine->getPack()->getSprite(3);
  _pawns[1] = _engine->getPack()->getSprite(4);
}

Field::~Field()
{
  delete (_hover);
  delete (_backGround);
  delete (_pawns[0]);
  delete (_pawns[1]);
}

void		Field::reset(){
  for (int i = 0; i < 361; i++){
    _field[i] = 0;
  }
  _lastInter.x = 0;
  _lastInter.y = 0;
}

void		Field::setCase(pawn *src, pawn dest){
  *src = ((*src) & gl_interest) + (dest & gl_player_part);
}

bool		Field::setPawn(t_position position, Player *player){
  position = getPosition(getId(position));

  if (!setPawn(position, player->getPawnPlayer()))
    return (false);
  player->setLastPawn(getId(position));
  pawn		*p = getInter(position);
  unsigned int	n;
  Patern	*pat = 0;
  unsigned int	i = 0;

  while ((pat = _arbitrator->getKillInter(i))){
    while (pat->match(this, position, *p, 0, &n)){
      p = _arbitrator->getInterPawn(this, pat, position, n, 1);
      if (p)
	*p = gl_empty;
      p = _arbitrator->getInterPawn(this, pat, position, n, 2);
      if (p)
	*p = gl_empty;
      player->addStone();
      p = getInter(position);
    }
    i++;
  }

  return (true);
}

bool		Field::setPawn(t_position pos, pawn owner){
  if (!legalArgument(pos))
    return (false);
  pawn		*pawn = getInter(pos);
  if (!PAWN((*pawn), gl_empty))
    return (false);
  setCase(pawn, owner);
  setHexaInterest(pos);
  return (true);
}

void		Field::setMouse(t_position pos){
  _mouse = pos;
}

int		Field::getId(t_position pos) const{
  if (!legalArgument(pos))
    return (-1);
  return ((pos.x / _sizeInter) % 19 + (pos.y / _sizeInter) * 19);
}

bool		Field::legalArgument(int id) const{
  return (id >= 0 && id < 361);
}

bool		Field::legalArgument(t_position pos) const{
  return (pos.x >= 0 && pos.x < (360 * _sizeInter) &&
	  pos.y >= 0 && pos.y < (360 * _sizeInter));
}

t_position	Field::getPosition(int id) const {
  t_position	t;
  t.x = id % 19 * _sizeInter;
  t.y = id / 19 * _sizeInter;
  return (t);
}

pawn		*Field::getInter(t_position pos){
  return (getInter(getId(pos)));
}

pawn		*Field::getInter(){
  return (getInter(getId(_mouse)));
}

pawn		*Field::getInter(int id){
  if (id < 0 || id > 360)
    return (0);
  return (&_field[id]);
}

pawn		*Field::getInter(int x, int y){
  return (getInter((x / _sizeInter) % 19 + (y / _sizeInter) * 19));
}

bool		Field::hover(int id){
  if (legalArgument(id))
    return (hover(getPosition(id)));
  return (false);      
}

bool		Field::hover(t_position pos){
  pawn *p = getInter(pos);
  if (!p || !PAWN((*p), 0))
    return (false);
  if (!legalArgument(pos))
    return (false);
  pos = getPosition(getId(pos));
  _hover->setPosition(pos.x, pos.y);
  _engine->getRender()->draw(*_hover);
  return (true);
}

bool		Field::put(int id){
  if (!legalArgument(id))
    return (false);
  return (put(getPosition(id)));
}

bool		Field::put(t_position pos){
  pawn *p = getInter(pos);
  if (!p)
    return (false);
  // Arbitrator
  return (true);
}

void		Field::draw(){
  _engine->getRender()->draw(*_backGround);

  for (int i = 0; i < 361; i++){
    drawPawn(_field[i], getPosition(i));
  }
}

void		Field::drawMonster(t_position pos){
  if (legalArgument(pos)){
    _monster->setPosition(pos.x, pos.y);
    _engine->getRender()->draw(*_monster);
  }
}

void		Field::drawPawn(pawn i, t_position pos){
  int		n = 0;

  if (PAWN(i, gl_player_1))
    n = 0;
  else if (PAWN(i, gl_player_2))
    n = 1;
  else{
    if ((i & gl_interest_part) != gl_empty && PAWN(i, gl_empty) && _drawMonster)
      drawMonster(pos);
    return;
  }
  _pawns[n]->setPosition(pos.x, pos.y);
  _engine->getRender()->draw(*_pawns[n]);
}

void		Field::changeMonster(){
  _drawMonster = !_drawMonster;
}

Engine		*Field::getEngine(){
  return (_engine);
}

Arbitrator	*Field::getArbitrator(){
  return (_arbitrator);
}

t_position	*Field::getCopyPosition(t_position p){
  t_position	*pos;
  pos = new t_position;

  pos->x = p.x;
  pos->y = p.y;
  return (pos);
}

t_position	Field::addPosition(t_position pos, int x, int y){
  pos.x += x;
  pos.y += y;
  return (pos);
}

void		Field::setHexaInterest(t_position pos){
  setInterest(addPosition(pos, -50, -50));
  setInterest(addPosition(pos, -50, 0));
  setInterest(addPosition(pos, -50, 50));
  setInterest(addPosition(pos, 0, -50));
  setInterest(addPosition(pos, 0, 50));
  setInterest(addPosition(pos, 50, -50));
  setInterest(addPosition(pos, 50, 0));
  setInterest(addPosition(pos, 50, 50));
}

void		Field::setInterest(t_position pos){
  pawn		*p = getInter(pos);
  if (!p || !legalArgument(pos))
    return;
  *p = gl_interest + ((*p) & gl_player_part);
}

pawn		*Field::getBoard(bool copy){
  if (!copy)
    return (_field);
  pawn		*p = new pawn[361];
  for (int i = 0; i < 361; i++)
    p[i] = _field[i];
  return (p);
}
