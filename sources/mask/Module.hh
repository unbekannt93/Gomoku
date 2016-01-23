#ifndef			MODULE_HH_
# define		MODULE_HH_

# include		<string>
# include		<SFML/Graphics.hpp>
# include		<SFML/Audio.hpp>
# include		"Click.hh"

class Engine;

class Module
{
public:
  Module(Engine *, std::size_t = 0, std::size_t = 0);
  virtual		~Module();
  virtual		void drawModule();
  virtual		void eventModule();
  virtual		void updateModule();
  virtual		void closeModule();
  virtual		void openModule();
  virtual		void setPosition(int, int);
  virtual		void setPosition(t_position);
  int			getX() const;
  int			getY() const;
  t_position		getPosition() const;
protected:
  Engine		*_engine;
  sf::Sprite		*_bg;
  sf::Music		*_loopSong;
  t_position		_position;
};

#endif
