#include "Screen.hh"

Screen::Screen() : _view(sf::FloatRect(0, 0, 1280, 720)), _rateX(0), _rateY(0),
		   _boardX(0), _boardY(0)
{

}

Screen::~Screen()
{

}

void		Screen::resizeView(float w, float h, sf::RenderWindow *render)
{
  float		rate;
  float		board;

  if (w / 16 >= h / 9)
    {
      rate = h / 9;
      board = ((w - (16 * rate)) / w);
      _boardX = (board / 2) * w;
      _boardY = 0;
      _view.setViewport(sf::FloatRect(board / 2, 0, 1 - board, 1));
    }
  else
    {
      rate = w / 16;
      board = ((h - (9 * rate)) / h);
      _boardX = 0;
      _boardY = (board / 2) * h;
      _view.setViewport(sf::FloatRect(0, board / 2, 1, 1 - board));
    }
  render->setView(_view);
  _rateX = 1280 / (16 * rate);
  _rateY = 720 / (9 * rate);
}

sf::View	&Screen::getView()
{
  return (_view);
}

int		Screen::getX(int x)
{
  int		r = x * _rateX - _boardX * _rateX;

  if (r < 0)
    return (0);
  if (r > 1280)
    return (1280);
  return (r);
}

int		Screen::getY(int y)
{
  int		r = y * _rateY - _boardY * _rateY;

  if (r < 0)
    return (0);
  if (r > 720)
    return (720);
  return (r);
}
