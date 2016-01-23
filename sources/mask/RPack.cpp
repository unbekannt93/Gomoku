#include	<iostream>
#include	<sstream>
#include	"RPack.hh"

RPack::RPack(sf::RenderWindow *r) : _render(r)
{
  _textures.push_back(sf::Texture());
  _textures[0].loadFromFile("Sources/papillusion.jpg");
  _textures.push_back(sf::Texture());
  _textures[1].loadFromFile("Sources/player.png");
  _textures.push_back(sf::Texture());
  _textures[2].loadFromFile("Sources/board.png");
  _textures.push_back(sf::Texture());
  _textures[3].loadFromFile("Sources/whiteStone.png");
  _textures.push_back(sf::Texture());
  _textures[4].loadFromFile("Sources/blackStone.png");
  _textures.push_back(sf::Texture());
  _textures[5].loadFromFile("Sources/startTheGame.png");
  _textures.push_back(sf::Texture());
  _textures[6].loadFromFile("Sources/playerOne.png");
  _textures.push_back(sf::Texture());
  _textures[7].loadFromFile("Sources/playerTwo.png");
}

RPack::~RPack()
{
  for (std::size_t i = 0; i < _musics.size(); i++)
    delete (_musics[i]);
  for (std::size_t i = 0; i < _songs.size(); i++)
    delete (_songs[i]);
}

sf::Sprite	*RPack::getSprite(std::size_t a) const
{
  // à changer en new sf::Sprite(_textures[0])
  if (a >= _textures.size())
    return (new sf::Sprite(_textures[0]));
  //______________________________________
  return (new sf::Sprite(_textures[a]));
}

sf::Texture	&RPack::getTexture(std::size_t a)
{
  if (a >= _textures.size())
    return (_textures[0]);
  return (_textures[a]);
}

sf::Music	*RPack::getMusic(std::size_t a) const
{
  if (a >= _musics.size())
    return (0);
  return (_musics[a]);
}

sf::Sound	*RPack::getSong(std::size_t a) const
{
  if (a >= _songs.size())
    return (_songs[0]);
  return (_songs[a]);
}

void		RPack::load()
{
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Font font;
  sf::Text txt;

  font.loadFromFile("Sources/font.ttf");
  txt.setFont(font);
  txt.setString("Loading...");
  txt.setCharacterSize(60);
  txt.setPosition(350, 275);
  txt.setColor(sf::Color::Black);
  texture.loadFromFile("Sources/load.png");
  sprite.setTexture(texture);
  _render->draw(sprite);
  _render->draw(txt);
  _render->display();
}
