#ifndef TREEMANAGER_HH_
#define TREEMANAGER_HH_

#include <string>

class Field;

class TreeManager
{
public:
  TreeManager(Field*, unsigned int = 3);
  ~TreeManager();
private:
  Field	*_field;
  unsigned int	depth;
};

#endif
