inherit "room/room";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
add_local_unique(CEMETARY+NPC+"cat");
set_light(1);
set_outdoors(1);
set_short("Pet Cemetary");
set_long_f(
  "A tall metal fence encases this pet cemetary. A small gateway is to "+
  "the east. All around are miniature tombstones, partially obscured by "+
  "overgrown grass.",FORMAT);
items=({
  ({"fence","metal fence","tall metal fence","tall fence"}),
   "A tall fence made of metal rods.",
  ({"rods","metal rods"}),
   "They make up the fence. The gap between them is generally not more than 20cm.",
  ({"gateway","small gateway"}),
   "A small gateway in the tall metal fence.",
  ({"tombstones","miniature tombstones"}),
   "Miniature tombstones.",
  ({"grass","overgrown grass","long overgrown grass"}),
   "Long, overgrown grass.",
  });
add_exit("east",CEMETARY+ROOM+"cem7");
}