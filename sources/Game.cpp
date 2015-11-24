#include <iostream>
#include "Game.hh"
#include "Engine.hh"

Game::Game(Engine *e, std::size_t bg,
	   std::size_t music) : Module(e, bg, music), _field(_engine), _currentPlayer(0)
{
  _players[0] = new Humain(&_field, _engine->getPack()->getSprite(3));
  _players[1] = new Humain(&_field, _engine->getPack()->getSprite(4));
}

Game::~Game()
{

}

void		Game::drawModule()
{
  if (_bg)
    _engine->getRender()->draw(*_bg);
  _field.draw();
}

void		Game::eventModule()
{
  if (_engine->getEvent()->type == sf::Event::MouseButtonPressed){
    if (_engine->getEvent()->mouseButton.button == sf::Mouse::Left){
      _players[_currentPlayer]->action(_field.getInter(_position));
    }
  }
}

void		Game::updateModule()
{
  if (_players[_currentPlayer]->haveFinished()){
    if (_players[0]->getBrain() == Player::WIN){
      std::cout << "Le joueur 1 gagne la partie" << std::endl;
      _engine->getRender()->close();
    }else if (_players[1]->getBrain() == Player::WIN){
      std::cout << "Le joueur 2 gagne la partie" << std::endl;
      _engine->getRender()->close();
    }
    _players[_currentPlayer]->sleep();
    _currentPlayer = 1 - _currentPlayer;
    _players[_currentPlayer]->turnBegin();
  }
}

void		Game::openModule()
{
  if (_loopSong)
    {
      _loopSong->setLoop(true);
      _loopSong->play();
    }
  _players[0]->turnBegin();
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
