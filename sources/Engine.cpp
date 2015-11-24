#include		<iostream>
#include		"Engine.hh"

Engine::Engine() : _render(sf::VideoMode(950, 950), "Gomoku"),
		   _res(&_render),
		   _cModule(0), _th(&Engine::updater, this),
		   _useScreen(false)
{
  sf::Vector2u	size = _render.getSize();
  if (_useScreen)
    _screen.resizeView(size.x, size.y, &_render);
  _modules[0] = new Game(this, 0, 0);
  _modules[_cModule]->openModule();
  //_th.launch();
}

Engine::~Engine()
{
  // ne pas oublier de mettre le bon nombre de Modules

  for (std::size_t i = 0; i < 1; i++)
    delete (_modules[i]);
}

void			Engine::start()
{
  _render.setFramerateLimit(30);
  while (_render.isOpen())
    {
      while (_render.pollEvent(_event))
	{
	  if (_event.type == sf::Event::Closed)
	    _render.close();
	  else if (_event.type == sf::Event::MouseMoved)
	    {
	      if (_useScreen)
		_modules[_cModule]->setPosition(_screen.getX(_event.mouseMove.x),
						_screen.getY(_event.mouseMove.y));
	      else
		_modules[_cModule]->setPosition(_event.mouseMove.x, _event.mouseMove.y);
	    }
	  else if (_event.type == sf::Event::KeyPressed)
	    {
	      if (_event.key.code == sf::Keyboard::Escape)
		_render.close();
	    }
	  else if (_event.type == sf::Event::Resized && _useScreen)
	    _screen.resizeView(_event.size.width, _event.size.height, &_render);
	  else
	    _modules[_cModule]->eventModule();
	}
      _modules[_cModule]->updateModule();
      _render.clear();
      _modules[_cModule]->drawModule();
      _render.display();
    }
}

void			Engine::setModule(std::size_t a)
{
  _modules[_cModule]->closeModule();
  _modules[a]->openModule();
  _modules[a]->setPosition(_modules[_cModule]->getX(), _modules[_cModule]->getY());
  _cModule = a;
}

void			Engine::updater()
{
  sf::sleep(sf::milliseconds(10));
  _modules[_cModule]->updateModule();
}

sf::RenderWindow	*Engine::getRender()
{
  return (&_render);
}

sf::Event		*Engine::getEvent()
{
  return (&_event);
}

RPack			*Engine::getPack()
{
  return (&_res);
}
