inherit "room/room";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_light(1);
set_outdoors(1);
set_short("Center of the Cemetary, on a path");
set_long_f(
  "A rugged stone path leads north towards an ominous house and "+
  "south towards the front gates of the cemetary. You are flanked "+
  "on both sides by a clearing of heavily decayed tombstones.",FORMAT);
items=({
  ({"gates","front gates"}),
   "They are bent, mangled, and gaping open.",
  ({"path","stone path","rugged stone path"}),
   "It stretches north towards an ominous house and "+
   "south towards the front gates of the cemetary.",
  ({"house","ominous house"}),
   "An ominous house at the end of the cemetary.",
  ({"tombstones","decayed tombstones","heavily decayed tombstones"}),
   "Heavily decayed tombstones.",
  });
add_exit("south", CEMETARY+ROOM+"cem2");
add_exit("north",CEMETARY+ROOM+"cem8");
add_exit("west",CEMETARY+ROOM+"cem4");
add_exit("east",CEMETARY+ROOM+"cem6");
}
