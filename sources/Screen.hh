#ifndef		SCREEN_HH_
# define	SCREEN_HH_

#include	<string>
#include	<SFML/Graphics.hpp>
#include	<SFML/Audio.hpp>

class Screen
{
public:
  Screen();
  ~Screen();
  void		resizeView(float, float, sf::RenderWindow*);
  sf::View	&getView();
  int		getX(int);
  int		getY(int);
private:
  sf::View	_view;
  float		_rateX;
  float		_rateY;
  float		_boardX;
  float		_boardY;
};

#endif
