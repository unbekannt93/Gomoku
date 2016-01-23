#ifndef CLICK_HH_
#define CLICK_HH_

struct		t_position{
  int		x;
  int		y;
};

struct		Click
{
  enum		Action{
    LEFT_CLICK,
    RIGHT_CLICK,
    OTHER
  };

  t_position	position;
  Action	action;
};


#endif
