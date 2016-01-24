#include "RuleMenu.hh"
#include "Engine.hh"
#include "Field.hh"
#include "Game.hh"

RuleMenu::RuleMenu(Engine *e, Field *f) : _engine(e), _field(f), _back(0),
					  _point(40.0f),
					  _stagePoint(15.0f),
					  _stage(0)
{
  for (int i = 0; i < 4; i++){
    _rules[i][0].x = 590;
    _rules[i][0].y = 180 + 130 * i;

    _rules[i][1].x = 795;
    _rules[i][1].y = _rules[i][0].y;
  }
  _back = _engine->getPack()->getSprite(9);
  _point.setFillColor(sf::Color::Transparent);
  _point.setOutlineColor(sf::Color::Red);
  _point.setOutlineThickness(3.0f);
  _point.setPosition(145, 835);

  _stagePoint.setFillColor(sf::Color::Blue);
}

RuleMenu::~RuleMenu()
{
  
}

void		RuleMenu::draw(){
  _engine->getRender()->draw(*_back);

  for (int i = 0; i < 4; i++){
    _point.setPosition(_rules[i][BOOLTOINT(_field->getArbitrator()->getRule(i))]);
    _engine->getRender()->draw(_point);
  }
  
  _point.setPosition(85 + 112 * (_field->getArbitrator()->getLevelAI() - 1), 810);
  _engine->getRender()->draw(_point);

  if (_stage == 4)
    _stagePoint.setPosition(15, 840);
  else
    _stagePoint.setPosition(15, 210 + 130 * _stage);
  _engine->getRender()->draw(_stagePoint);
}

void		RuleMenu::event(){
  if (_engine->getEvent()->type == sf::Event::KeyPressed){
    if (_engine->getEvent()->key.code == sf::Keyboard::Down)
      _stage = (_stage + 1) % 5;
    else if (_engine->getEvent()->key.code == sf::Keyboard::Up)
      _stage = (_stage + 4) % 5;
    else if (_engine->getEvent()->key.code == sf::Keyboard::Left){
      if (_stage == 4)
	_field->getArbitrator()->setLevelAI(_field->getArbitrator()->getLevelAI() - 1);
      else
	_field->getArbitrator()->setRule(_stage, !_field->getArbitrator()->getRule(_stage));
    }
    else if (_engine->getEvent()->key.code == sf::Keyboard::Right){
      if (_stage == 4)
	_field->getArbitrator()->setLevelAI(_field->getArbitrator()->getLevelAI() + 1);
      else
	_field->getArbitrator()->setRule(_stage, !_field->getArbitrator()->getRule(_stage));
    }
  }
}
