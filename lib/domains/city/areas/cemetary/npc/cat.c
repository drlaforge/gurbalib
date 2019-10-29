inherit "obj/walkingmonster.c";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("cat");
set_short ("a cat");
set_long_f("A mangy cat.",FORMAT);
set_id(({"cat","mangy cat"}));
set_level(1);
set_walking(25);
setmout ("A cat stalks #D");
setmin ("A cat stalks in");
}
