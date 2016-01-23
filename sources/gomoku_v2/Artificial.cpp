#include "Artificial.hh"
#include "Field.hh"
#include "AITree.hh"
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
  //std::cout << "ENTER" << std::endl;
  //_tree = new AITree(_field, _owner, _field->getBoard(), _depth);
  _tree = new ABTree(_field, _owner);
  _tree->buildTree();
  //delete(_tree);
  _tree = 0;
  //std::cout << "DONE" << std::endl;
  _brain = Player::FINISHED;
}
