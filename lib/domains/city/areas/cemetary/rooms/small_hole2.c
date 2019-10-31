inherit "room/room"; /* Hole with nothing. */
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_outdoors(1);
set_light(1);
set_short("A hole");
set_long_f(
  "The hole is roughly two meters deep. "+
  "A skeleton lies mangled and broken at the bottom.",
  FORMAT);
items=({"skeleton","It is mangled and broken.",});
add_exit("out",CEMETARY+ROOM+"cem4");
}
