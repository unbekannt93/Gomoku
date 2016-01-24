#include "MainMenu.hh"
#include "Engine.hh"
#include <iostream>

MainMenu::MainMenu(Engine *e, std::size_t bg, std::size_t music) : Module(e, bg, music),
								   _one(600, 630, 230, 70),
								   _two(600, 700, 230, 70)
{
  
}

MainMenu::~MainMenu()
{
  
}

void		MainMenu::drawModule()
{
  _engine->getRender()->draw(*_bg);
}

void		MainMenu::eventModule()
{
  if (_engine->getEvent()->type == sf::Event::MouseButtonPressed){
    if (_one.tryClick(_position)){
      _engine->setParams(0);
      _engine->setModule(1);
    }else if (_two.tryClick(_position)){
      _engine->setParams(1);
      _engine->setModule(1);
    }
  }
}

void		MainMenu::updateModule()
{
  //std::cout << _position.x << ";" << _position.y << std::endl;
}

void		MainMenu::openModule()
{
  if (_loopSong)
    {
      _loopSong->setLoop(true);
      _loopSong->play();
    }
  _engine->getRender()->setMouseCursorVisible(true);
}

void		MainMenu::closeModule()
{
  if (_loopSong)
    _loopSong->stop();
}
