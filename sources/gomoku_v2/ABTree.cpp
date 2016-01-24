#include "ABTree.hh"
#include "Field.hh"

ABTree::ABTree(Field *f, ABTree *ab, int id, pawn p,
	       int min, int max, bool isMax, int d) : _field(f), _parent(ab),
						      _id (id), _player(p),
						      _min(min), _max(max),
						      _isMax(isMax), _depth(d),
						      _score(0), _child(0)
{
  _position = _field->getPosition(_id);
}

ABTree::ABTree(Field *f, pawn p, bool isMax, int d) : _field(f), _parent(0),
						      _id (-1), _player(p),
						      _min(-gl_infini),
						      _max(gl_infini),
						      _isMax(isMax), _depth(d),
						      _score(0), _child(0)
{

}

ABTree::~ABTree()
{
  if (_child)
    delete (_child);
}

bool	ABTree::myInterest(pawn i){
  return (i != 0 && i < DEPTHINTEREST(_depth));
}

int	ABTree::buildTree(){
  pawn		*inter;
  ABTree	*newTree;
  int		n;
  bool		canPlace;

  pawn		me = gl_player_1;
  if (PAWN(_player, gl_player_1))
    me = gl_player_2;
  setHexaInterest(_player);
  if (_depth <= 0){
    setHexaInterest(gl_empty, false);
    return (getScore());
  }

  for (unsigned int i = 0; i < 361; i++){
    inter = _field->getInter(i);
    if (inter && myInterest((*inter) & gl_interest_part) && PAWN((*inter), gl_empty)){
      newTree = new ABTree(_field, this, i, me,
			   _min, _max, !_isMax, _depth-1);
      n = newTree->buildTree();
      canPlace = _field->getArbitrator()->canPlace(_player, _field->getPosition(i));
      if (_isMax && n > _min && canPlace){
	_min = n;
	if (_child)
	  delete (_child);
	_child = newTree;
      }else if (!_isMax && n < _max && canPlace){
	_max = n;
	if (_child)
	  delete (_child);
	_child = newTree;
      }else{
	if (_child)
	  delete (_child);
	_child = newTree;
	setHexaInterest(gl_empty, false);
	if (_isMax)
	  return (_min);
	return (_max);
      }
    }
  }
  setHexaInterest(gl_empty, false);
  if (_isMax)
    return (_min);
  return (_max);
}

void	ABTree::setHexaInterest(pawn p, bool set){
  pawn *board = _field->getBoard(false);
  if (!board || _id < 0 || _id > 361)
    return;
  board[_id] = (board[_id] & gl_interest_part) + p;  
  setInterest(_id - 1, set);
  setInterest(_id + 1, set);
  setInterest(_id - 18, set);
  setInterest(_id - 19, set);
  setInterest(_id - 20, set);
  setInterest(_id + 18, set);
  setInterest(_id + 19, set);
  setInterest(_id + 20, set);
  
}

void	ABTree::setInterest(int id, bool set){
  pawn *board = _field->getBoard(false);
  if (!board || id < 0 || id > 360)
    return;
  pawn interest = DEPTHINTEREST(_depth);
  if (set){
    board[id] = board[id] | interest;
  }
  else{
    board[id] = board[id] & (~interest);
  }
}

int	ABTree::getScore(){
  if (!_field->legalArgument(_position))
    return (0);
  Arbitrator	*a = _field->getArbitrator();
  Patern	*p = 0;
  unsigned int	i = 0;
  unsigned int	n = 0;
  pawn		*board = _field->getBoard(false);

  while ((p = a->getWinInter(i))){
    n = MAX(n, (p->matchPercent(_field, board, _position, _player) * 5));
    i++;
  }
  if (n == 100)
    return (gl_infini);

  _score += n;
  i = 0;
  n = 0;
  while ((p = a->getKillInter(i))){
    n = MAX(n, (p->matchPercent(_field, board, _position, _player) * 3));
    i++;
  }
  _score += n;

  i = 0;
  n = 0;
  while ((p = a->getThreeInter(i))){
    n = MAX(n, (p->matchPercent(_field, board, _position, _player) * 2));
    i++;
  }
  _score += n;
  return (_score);
}

int	ABTree::getIdChild() const{
  if (!_child)
    return (-1);
  return (_child->getId());
}

int	ABTree::getId() const{
  return (_id);
}
