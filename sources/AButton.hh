#ifndef ABUTTON_HH_
#define ABUTTON_HH_

# include <string>
# include <SFML/Graphics.hpp>
# include "Click.hh"

class AButton
{
public:
  AButton(int l, int t, int w, int h);
  AButton(sf::IntRect&);
  ~AButton();
  void	onClick(Click&);
  bool	tryClick(Click&);
virtual void	leftClick() = 0;
virtual void	rightClick() = 0;
virtual void	otherClick() = 0;
private:
  sf::IntRect	_rect;
};

#endif
