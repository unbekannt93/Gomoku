#ifndef MAINMENU_HH_
#define MAINMENU_HH_

#include <string>
#include "Module.hh"
#include "AButton.hh"

class Engine;

class MainMenu : public Module
{
public:
  MainMenu(Engine*, std::size_t, std::size_t);
  ~MainMenu();
  void drawModule();
  void eventModule();
  void updateModule();
  void closeModule();
  void openModule();
private:
  AButton	_one;
  AButton	_two;
};

#endif
