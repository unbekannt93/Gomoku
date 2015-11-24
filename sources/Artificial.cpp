#include "Artificial.hh"
#include "Field.hh"

Artificial::Artificial(Field *f, sf::Sprite *s) : Player(f, s)
{

}
Artificial::~Artificial()
{

}

void			Artificial::action(Intersection *i){
  (void)i;
}
