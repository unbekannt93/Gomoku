#include "AITree.hh"
#include "Field.hh"
#include "Player.hh"
#include "Patern.hh"

AITree::AITree(Field *field, pawn player, pawn *f,
	       int depth) : _field(field), _player(player), _board(f),
			    _points(0), _depth(depth), _id(-1),
			    _th(&AITree::buildTree, this),
			    _max(true)
{
  _branch.clear();
  buildTree();
}


AITree::AITree(Field *field, pawn player, pawn *f, t_position pos,
	       int depth, bool max) : _field(field), _player(player), _board(f),
				      _points(0), _depth(depth),
				      _th(&AITree::buildTree, this),
				      _max(max)
{
  int	id = _field->getId(pos);
  _id = id;
  if (_field->legalArgument(id))
    setHexaInterest(id);
  _branch.clear();
  buildTree();
}

AITree::AITree(Field *field, pawn player, pawn *f, int id,
	       int depth, bool max) : _field(field), _player(player), _board(f),
				      _points(0), _depth(depth), _id(id),
				      _th(&AITree::buildTree, this),
				      _max(max)
{
  if (_field->legalArgument(id))
    setHexaInterest(id);
  _branch.clear();
  buildTree();
}

AITree::~AITree()
{
  for (unsigned int i = 0; i < _branch.size(); i++)
    delete (_branch[i]);
  if (_board)
    delete [](_board);
}

void	AITree::buildTree(){
  if (_depth <= 0){
    if (_id != -1)
      getPoints();
    return;
  }
  _branch.clear();
  for (unsigned int i = 0; i < 361; i++){
    if (BIT(_board[i], gl_interest)){
      _branch.push_back(new AITree(_field, _player, copyBoard(), i, _depth-1, !_max));
    }
  }
  for (unsigned int i = 0; i < _branch.size(); i++)
    _branch[i]->wait();
}

void	AITree::setHexaInterest(int id){
  _board[id] = (_board[id] & gl_interest) + (_player & gl_player_part);
  setInterest(id - 1);
  setInterest(id + 1);
  setInterest(id - 18);
  setInterest(id - 19);
  setInterest(id - 20);
  setInterest(id + 18);
  setInterest(id + 19);
  setInterest(id + 20);
}

void	AITree::setInterest(int id){
  if (id < 0 || id > 360)
    return;
  _board[id] = gl_interest + (_board[id] & gl_player_part);
}

pawn	*AITree::copyBoard(){
  pawn	*p = new pawn[361];
  if (!p)
    return (0);
  for (int i = 0; i < 361; i++)
    p[i] = _board[i];
  return (p);
}

void	AITree::getPoints(){
  t_position	pos = _field->getPosition(_id);
  if (!_field->legalArgument(pos) || !_field->legalArgument(_id))
    return;
  Arbitrator	*a = _field->getArbitrator();
  Patern	*p = 0;
  unsigned int	i = 0;
  unsigned int	n = 0;

  while ((p = a->getWinInter(i))){
    n = MAX(n, (p->matchPercent(_field, _board, pos, _player) * 1));
    i++;
  }
  if (n == 100){
    _points = gl_infini;
    return;
  }
  _points += n;

  i = 0;
  n = 0;
  while ((p = a->getKillInter(i))){
    n = MAX(n, (p->matchPercent(_field, _board, pos, _player) * 3));
    i++;
  }
  _points += n;

  i = 0;
  n = 0;
  while ((p = a->getThreeInter(i))){
    n = MAX(n, (p->matchPercent(_field, _board, pos, _player) * 2));
    i++;
  }
  _points += n;
}

void		AITree::wait(){
  _th.wait();
}

int		AITree::getPoints() const{
  return (_points);
}

AITree		*AITree::getBetter(int min, int max){
  (void)min;
  (void)max;
  return (0);
}

bool		AITree::isEnd() const{
  return (_branch.size() == 0);
}
