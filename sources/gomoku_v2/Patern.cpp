#include "Patern.hh"
#include <iostream>

Patern::Patern(int player)
{
  addCase(0, 0, player);
}

Patern::~Patern()
{

}

void		Patern::addCase(t_position pos, int player){
  addCase(pos.x, pos.y, player);
}

void		Patern::addCase(int x, int y, int player){
  Patern::PaternCase	p;

  p.pos.x = x * 50;
  p.pos.y = y * 50;
  p.player = player;
  _patern.push_back(p);
}

t_position	Patern::subPosition(t_position a, t_position b){
  b.x -= a.x;
  b.y -= a.y;
  return (b);
}

t_position	Patern::addPosition(t_position a, t_position b){
  b.x += a.x;
  b.y += a.y;
  return (b);
}

bool		Patern::matchInter(Patern::PaternCase c, pawn p, pawn owner){
  if (c.player == 0){
    return (PAWN(p, owner));
  }else if (c.player == 1){
    return (!PAWN(p, owner) && !PAWN(p, gl_empty) && !PAWN(owner, gl_empty));
  }else if (c.player == 2){
    return (!PAWN(p, gl_empty) && !PAWN(owner, gl_empty));
  }else if (c.player == 3){
    return (PAWN(owner, gl_empty));
  }
  return (true);
}

bool		Patern::match(Field *f, t_position pos, pawn p, int position, unsigned int *ptr){
  if (position >= (int)_patern.size())
    return (false);
  pos = f->getPosition(f->getId(pos));
  t_position	start = subPosition(_patern[position].pos, pos);
  t_position	tmp;
  pawn		*ptmp = f->getInter(tmp);
  pawn		comparator = p;

  for (unsigned int i = 0; i < _patern.size(); i++){
    tmp = addPosition(_patern[i].pos, start);
    ptmp = f->getInter(tmp);

    if (!f->legalArgument(tmp) || !ptmp)
      return (match(f, pos, p, position+1, ptr));
    if (f->getId(pos) == f->getId(tmp))
      comparator = p;
    else
      comparator = *ptmp;
    if (!matchInter(_patern[i], p, comparator))
      return (match(f, pos, p, position+1, ptr));
  }
  if (ptr)
    *ptr = position;
  return (true);
}

unsigned int	Patern::getSize(){
  return (_patern.size());
}

Patern::PaternCase	*Patern::getCase(unsigned int i){
  if (i >= _patern.size())
    return (0);
  return (&_patern[i]);
}

pawn		*Patern::getPawnInBoard(Field *f, pawn *board, t_position pos){
  if (!f->legalArgument(pos) || !f->legalArgument(f->getId(pos)))
    return (0);
  return (&(board[f->getId(pos)]));
}

unsigned int	Patern::matchMax(Field *f, pawn *board, t_position pos, pawn p, int position){
  if (position >= (int)_patern.size())
    return (0);

  pos = f->getPosition(f->getId(pos));

  t_position	start = subPosition(_patern[position].pos, pos);
  t_position	tmp;
  pawn		*ptmp = getPawnInBoard(f, board, tmp);
  pawn		comparator = p;

  for (unsigned int i = 0; i < _patern.size(); i++){
    tmp = addPosition(_patern[i].pos, start);
    ptmp = getPawnInBoard(f, board, tmp);

    if (!f->legalArgument(tmp) || !ptmp)
      return (MAX(i, matchMax(f, board, pos, p, position+1)));
    if (f->getId(pos) == f->getId(tmp))
      comparator = p;
    else
      comparator = *ptmp;
    if (!matchInter(_patern[i], p, comparator))
      return (MAX(i, matchMax(f, board, pos, p, position+1)));
  }
  return (_patern.size());
}

unsigned int	Patern::matchPercent(Field *f, pawn *board, t_position pos, pawn p){
  return (PERCENT(matchMax(f, board, pos, p), _patern.size()));
}
