inherit "obj/walkingmonster.c";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("rabbit");
set_short ("a rabbit");
set_long_f("A fluffy rabbit.",FORMAT);
set_id("fluffy rabbit");
set_level (1);
set_walking(25);
setmout ("A rabbit hops #D");
setmin ("A rabbit hops in");
}
