#include "Artificial.hh"
#include "Field.hh"
#include "ABTree.hh"

Artificial::Artificial(Field *f, sf::Sprite *s, pawn p,
		       int depth) : Player(f, s, p), _depth(depth), _tree(0)
{

}

Artificial::~Artificial()
{
  if (_tree)
    delete (_tree);
}

void			Artificial::action(t_position pos){
  (void)pos;
}

void			Artificial::turnBegin(){
  _brain = Player::THINK;
  think();
}

void			Artificial::think(){
  _tree = new ABTree(_field, _owner, true, _field->getArbitrator()->getLevelAI());
  _tree->buildTree();
  int id = _tree->getIdChild();
  delete(_tree);
  _tree = 0;
  t_position position = _field->getPosition(id);
  _field->setPawn(position, _owner);
  if (_field->getArbitrator()->playerWin(this, position))
    _brain = Player::WIN;
  else
    _brain = Player::FINISHED;
}
