inherit "obj/monster";
#include "../area.h"

reset(arg)          {
          ::reset(arg);
          if(arg) return;
          set_level(2);
set_name("boy");
set_short("a deformed boy");
set_long_f(
"A skinny, ugly, deformed boy.",FORMAT);
set_mass_defend(1);
}

id(str)
{
return str=="boy" ||
str=="deformed boy" || 
str=="ugly deformed boy" || 
str=="skinny ugly deformed boy";
}
