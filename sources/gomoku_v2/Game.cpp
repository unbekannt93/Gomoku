#include <iostream>
#include "Game.hh"
#include "Engine.hh"

Game::Game(Engine *e, std::size_t bg,
	   std::size_t music) : Module(e, bg, music), _winner(-1), _field(_engine), _currentPlayer(0),
				_exit(840, 800, 85, 70),
				_new(25, 800, 185, 70)
{
  _players[0] = new Humain(&_field, _engine->getPack()->getSprite(3), 1);
  //_players[1] = new Humain(&_field, _engine->getPack()->getSprite(4), 2);
  _players[1] = new Artificial(&_field, _engine->getPack()->getSprite(4), 2);

  _backEnd[0] = _engine->getPack()->getSprite(6);
  _backEnd[1] = _engine->getPack()->getSprite(7);
}

Game::~Game()
{

}

void		Game::reset(){
  _winner = -1;
  _field.reset();
  delete (_players[0]);
  delete (_players[1]);
  
  _players[0] = new Humain(&_field, _engine->getPack()->getSprite(3), 1);
  _players[1] = new Humain(&_field, _engine->getPack()->getSprite(4), 2);
}

void		Game::drawModule()
{
  if (_winner != -1){
    _engine->getRender()->draw(*_backEnd[_winner]);
  }else{
    if (_bg)
      _engine->getRender()->draw(*_bg);
    _field.draw();
    _players[_currentPlayer]->hover(_position);
  }
}

void		Game::eventModule()
{
  if (_engine->getEvent()->type == sf::Event::MouseButtonPressed){
    if (_winner != -1){
      if (_exit.tryClick(_position)){
	_engine->setModule(0);
      }else if (_new.tryClick(_position)){
	_engine->setModule(1);
      }
    }else{
      if (_engine->getEvent()->mouseButton.button == sf::Mouse::Left){
	_players[_currentPlayer]->action(_position);
      }
    }
  }
}

void		Game::updateModule()
{
  if (_winner != -1)
    {
      //std::cout << _position.x << ":" << _position.y << std::endl;
      return;
    }
  if (_players[_currentPlayer]->haveFinished()){
    if (_players[0]->getBrain() == Player::WIN){
      /*
      std::cout << "Le joueur 1 gagne la partie" << std::endl;
      _engine->getRender()->close();
      */
      _winner = 0;
      _engine->getRender()->setMouseCursorVisible(true);
    }else if (_players[1]->getBrain() == Player::WIN){
      /*
      std::cout << "Le joueur 2 gagne la partie" << std::endl;
      _engine->getRender()->close();
      */
      _winner = 1;
      _engine->getRender()->setMouseCursorVisible(true);
    }else{
      _players[_currentPlayer]->sleep();
      _currentPlayer = 1 - _currentPlayer;
      _players[_currentPlayer]->turnBegin();
    }
  }
}

void		Game::openModule()
{
  if (_loopSong)
    {
      _loopSong->setLoop(true);
      _loopSong->play();
    }
  _engine->getRender()->setMouseCursorVisible(false);
  _currentPlayer = 0;
  _players[_currentPlayer]->turnBegin();
}

void		Game::closeModule()
{
  if (_loopSong)
    _loopSong->stop();
  reset();
  _engine->getRender()->setMouseCursorVisible(true);
}

void		Game::setPosition(int x, int y)
{
  _position.x = x;
  _position.y = y;
  _field.setMouse(_position);
}
