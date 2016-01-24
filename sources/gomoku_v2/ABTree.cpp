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
  for (unsigned int i = 0; i < _children.size(); i++)
    delete (_children[i]);
}

bool	ABTree::myInterest(pawn i){
  return (i != 0 && i < DEPTHINTEREST(_depth));
}

int	ABTree::buildTree(){
  pawn		*inter;
  ABTree	*newTree;
  int		n;

  setHexaInterest(_player);
  if (_depth <= 0){
    setHexaInterest(gl_empty, false);
    return (getScore());
  }
  _children.clear();

  for (unsigned int i = 0; i < 361; i++){
    inter = _field->getInter(i);
    if (inter && myInterest((*inter) & gl_interest_part) && PAWN((*inter), gl_empty)){
      newTree = new ABTree(_field, this, i,OPLAYER(((*inter) & gl_player_part)),
			   _min, _max, !_isMax, _depth-1);
      n = newTree->buildTree();
      if (_isMax && _min < n){
	_min = n;
	_child = newTree;
      }else if (!_isMax && _max > n){
	_max = n;
	_child = newTree;
      }
      _children.push_back(newTree);
    }
  }
  setHexaInterest(gl_empty, false);
  //std::cout << "+ " << _children.size() << std::endl;
  if (_isMax)
    return (_min);
  return (_max);
}

void	ABTree::setHexaInterest(pawn p, bool set){
  pawn *board = _field->getBoard(false);
  if (!board || _id < 0 || _id > 361)
    return;
  board[_id] = (board[_id] & gl_interest_part) + p;
  (void)set;
  
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
    n = MAX(n, (p->matchPercent(_field, board, _position, _player) * 1));
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
