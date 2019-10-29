inherit "obj/monster";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_level(1);
set_name("small bug");
set_id("bug");
set_short("a bug");
set_long_f(
"A small bug.",FORMAT);
set_kill_shout(0);
}
