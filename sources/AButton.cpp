#include "AButton.hh"

AButton::AButton(int l, int t, int w, int h) : _rect(sf::IntRect(l, t, w, h))
{

}

AButton::AButton(sf::IntRect &r) : _rect(r)
{

}

AButton::~AButton()
{

}

void	AButton::onClick(Click &c){
  if (c.action == Click::LEFT_CLICK){
    leftClick();
  }else if (c.action == Click::RIGHT_CLICK){
    rightClick();
  }else if (c.action == Click::OTHER){
    otherClick();
  }
}

bool	AButton::tryClick(Click &c){
  if (!_rect.contains(c.position.x, c.position.y)){
    return (false);
  }
  onClick(c);
  return (true);
}
