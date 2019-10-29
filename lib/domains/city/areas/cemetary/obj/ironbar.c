inherit "obj/weapon.c";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("ironbar");
set_short("an ironbar");
set_long_f("An ironbar. One end is a bit roughed up.",FORMAT);
set_wc(13);
set_weight(2);
set_value(100+random(200));
}
