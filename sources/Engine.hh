#ifndef			ENGINE_HH_
# define		ENGINE_HH_

# include		<string>
# include		<SFML/Graphics.hpp>
# include		<SFML/Audio.hpp>
# include		"RPack.hh"
# include		"Game.hh"
# include		"Screen.hh"

class Engine
{
public:
  Engine();
  ~Engine();
  void			start();
  void			setModule(std::size_t);
  void			updater();
  sf::RenderWindow	*getRender();
  sf::Event		*getEvent();
  RPack			*getPack();
private:
  sf::RenderWindow	_render;
  sf::Event		_event;
  RPack			_res;
  Module		*_modules[2];
  std::size_t		_cModule;
  sf::Thread		_th;
  Screen		_screen;
  bool			_useScreen;
};

#endif
