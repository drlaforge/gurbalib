inherit "obj/armour";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("overcoat");
set_short("Long dark overcoat");
set_long_f("A long dark overcoat, covered with patches.",FORMAT);
set_type("armour");
set_ac(9);
set_value(50+random(100));
set_weight(3);
}

id(str)
{
return str=="overcoat" ||
str=="dark overcoat" ||
str=="long dark overcoat";
}
