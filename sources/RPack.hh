#ifndef				RPACK_HH_
#define				RPACK_HH_

#include			<string>
#include			<SFML/Graphics.hpp>
#include			<SFML/Audio.hpp>

class				RPack
{
public:
  RPack(sf::RenderWindow*);
  ~RPack();
  sf::Sprite			*getSprite(std::size_t) const;
  sf::Texture			&getTexture(std::size_t);
  sf::Music			*getMusic(std::size_t a) const;
  sf::Sound			*getSong(std::size_t a) const;
  void				playSound(std::size_t);

  void				load();

private:
  std::vector<sf::Texture>	_textures;
  std::vector<sf::Music*>	_musics;

  std::vector<sf::SoundBuffer>	_buffers;
  std::vector<sf::Sound*>	_songs;

  sf::RenderWindow		*_render;
};

#endif
