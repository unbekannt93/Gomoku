#include "Module.hh"
#include "Engine.hh"

Module::Module(Engine *engine, std::size_t bg, std::size_t music) : _engine(engine)
{
  _position.x = 0;
  _position.y = 0;
  _bg = _engine->getPack()->getSprite(bg);
  _loopSong = _engine->getPack()->getMusic(music);
}
Module::~Module()
{
  if (_bg)
    delete (_bg);
  if (_loopSong)
    delete (_loopSong);
}

void		Module::drawModule()
{
  if (_bg)
    _engine->getRender()->draw(*_bg);
}

void		Module::eventModule()
{
  
}

void		Module::updateModule()
{
  
}

void		Module::openModule()
{
  if (_loopSong)
    {
      _loopSong->setLoop(true);
      _loopSong->play();
    }
}

void		Module::closeModule()
{
  if (_loopSong)
    _loopSong->stop();
}

void		Module::setPosition(int x, int y)
{
  _position.x = x;
  _position.y = y;
}

void		Module::setPosition(t_position pos)
{
  setPosition(pos.x, pos.y);
}

int		Module::getX() const
{
  return (_position.x);
}

int		Module::getY() const
{
  return (_position.y);
}

t_position	Module::getPosition() const
{
  return (_position);
}
