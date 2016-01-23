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
  bool	tryClick(t_position);
  virtual void	leftClick();
  virtual void	rightClick();
  virtual void	otherClick();
private:
  sf::IntRect	_rect;
};

#endif
