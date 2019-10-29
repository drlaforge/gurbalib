inherit "obj/monster";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_level(2);
set_name("girl");
set_short("a small girl");
set_long_f(
"A quiet, small girl.",FORMAT);
set_gender(2);
set_mass_defend(1);
}

id(str)
{
return str=="girl" ||
str=="small girl" ||
str=="quiet small girl";
}
