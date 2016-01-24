#include <iostream>
#include "Game.hh"
#include "Engine.hh"
#include <sstream>

Game::Game(Engine *e, std::size_t bg,
	   std::size_t music) : Module(e, bg, music), _winner(-1), _field(_engine), _currentPlayer(0),
				_exit(840, 800, 85, 70),
				_new(25, 800, 185, 70),
				_openTools(false),
				_rules(_engine, &_field),
				_scoring(false)
{
  _players[0] = new Humain(&_field, _engine->getPack()->getSprite(3), 1);

  if (_engine->getParams() == 1)
    _players[1] = new Humain(&_field, _engine->getPack()->getSprite(4), 2);
  else
    _players[1] = new Artificial(&_field, _engine->getPack()->getSprite(4), 2);

  _backEnd[0] = _engine->getPack()->getSprite(6);
  _backEnd[1] = _engine->getPack()->getSprite(7);

  _font.loadFromFile("Sources/shablagoo.ttf");
  _text.setFont(_font);
  _text.setCharacterSize(30);
  _text.setColor(sf::Color::Black);
}

Game::~Game()
{

}

std::string	Game::valueOf(int v){
  std::stringstream	ss;
  ss << v;
  return (ss.str());
}

void		Game::reset(){
  _winner = -1;
  _field.reset();
  delete (_players[0]);
  delete (_players[1]);

  _players[0] = new Humain(&_field, _engine->getPack()->getSprite(3), 1);

  if (_engine->getParams() == 1)
    _players[1] = new Humain(&_field, _engine->getPack()->getSprite(4), 2);
  else
    _players[1] = new Artificial(&_field, _engine->getPack()->getSprite(4), 2);
}

void		Game::drawModule()
{
  if (_winner != -1){
    _engine->getRender()->draw(*_backEnd[_winner]);
  }else if (_openTools){
    _rules.draw();
  }else{
    if (_bg)
      _engine->getRender()->draw(*_bg);
    _field.draw();
    _players[_currentPlayer]->hover(_position);

    if (_scoring){
      _text.setString("Player 1 : " + valueOf(_players[0]->getStoneKilled()) + " / 10");
      _text.setPosition(200, 0);
      _engine->getRender()->draw(_text);
      _text.setString("Player 2 : " + valueOf(_players[1]->getStoneKilled()) + " / 10");
      _text.setPosition(550, 0);
      _engine->getRender()->draw(_text);
    }
  }
}

void		Game::eventModule()
{
  if (_openTools){
    _rules.event();
  }
  if (_engine->getEvent()->type == sf::Event::KeyPressed &&
      _engine->getEvent()->key.code == sf::Keyboard::Tab){
    _openTools = !_openTools;
  }
  else if (_engine->getEvent()->type == sf::Event::KeyPressed &&
      _engine->getEvent()->key.code == sf::Keyboard::A && !_openTools)
    _field.changeMonster();
  else if (_engine->getEvent()->type == sf::Event::KeyPressed &&
      _engine->getEvent()->key.code == sf::Keyboard::S && !_openTools)
    _scoring = !_scoring;
  else if (_engine->getEvent()->type == sf::Event::MouseButtonPressed && !_openTools){
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
    return;
  if (_players[_currentPlayer]->haveFinished()){
    if (_players[0]->getBrain() == Player::WIN){
      _winner = 0;
      _engine->getRender()->setMouseCursorVisible(true);
    }else if (_players[1]->getBrain() == Player::WIN){
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
  reset();
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
  _engine->getRender()->setMouseCursorVisible(true);
}

void		Game::setPosition(int x, int y)
{
  _position.x = x;
  _position.y = y;
  _field.setMouse(_position);
}
