#include "Game.hh"

Game::Game(Engine *e, std::size_t bg,
	   std::size_t music) : Module(e, bg, music), _field(_engine), _currentPlayer(0)
{
  
}

Game::~Game()
{

}

void		Game::drawModule()
{
  if (_bg)
    _engine->getRender()->draw(*_bg);
}

void		Game::eventModule()
{
  
}

void		Game::updateModule()
{
  
}

void		Game::openModule()
{
  if (_loopSong)
    {
      _loopSong->setLoop(true);
      _loopSong->play();
    }
}

void		Game::closeModule()
{
  if (_loopSong)
    _loopSong->stop();
}

void		Game::setPosition(int x, int y)
{
  _position.x = x;
  _position.y = y;
  _field.setMouse(_position);
}
