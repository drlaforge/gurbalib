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
"A lively, small girl.",FORMAT);
load_chat(5,({
  "The small girl puts her hands on her hips flamboyantly.\n",
  "The small girl looks at the hole and whispers: Poor granny.\n",
  "The small girl screams loudly: If I ever catch the bastard who did this!\n",
  }));
set_gender(2);
set_mass_defend(1);
}

id(str)
{
return str=="girl" ||
str=="small girl" ||
str=="lively small girl";
}
