inherit "room/room";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
add_object(CEMETARY+NPC+"girl");
add_object(CEMETARY+NPC+"girl2");
set_light(1);
set_outdoors(1);
set_short("Western edge of the Cemetary");
set_long_f(
  "A tall metal fence is to your west. "+
  "A fairly large hole has been dug in front of the tombstone nearest to you. "+
  "Near the hole is a large pile of dirt.",FORMAT);
items=({
  ({"fence","metal fence","tall metal fence","tall fence"}),
   "A tall fence made of metal rods.",
  ({"rods","metal rods"}),
   "They make up the fence. The gap between them is generally not more than 20cm.",
  ({"tombstone","rock","piece of rock","cracked piece of rock"}),
   "The inscription has been scraped away by time. Now it is just a "+
   "cracked piece of rock sticking out of the ground.",
  ({"hole","large hole","fairly large hole"}),
   "A hole has been dug in front of the tombstone nearest to you. "+
   "It should be easy to go into.",
  ({"dirt","pile of dirt","large pile of dirt","pile","large pile"}),
   "A large pile of dirt lying against the fence.",
  });
add_exit("south",CEMETARY+ROOM+"cem1");
add_exit("north",CEMETARY+ROOM+"cem7");
add_exit("east",CEMETARY+ROOM+"cem5");
add_exit("hole",CEMETARY+ROOM+"small_hole2");
}
